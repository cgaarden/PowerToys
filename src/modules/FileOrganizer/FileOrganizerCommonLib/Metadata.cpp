#include "pch.h"
#include "Metadata.h"
#include <cmath>
#include <cwctype>
#include <memory>	
#include <propkey.h>
#include <ShlObj.h>
#include <stdexcept>
#include <chrono>
#include <thread>


MetadataReadWrite::~MetadataReadWrite()
{
	Close();
}

bool MetadataReadWrite::Open(const std::wstring& file_path) noexcept
{
	const HRESULT result = SHGetPropertyStoreFromParsingName(file_path.c_str(), NULL, GPS_READWRITE, IID_PPV_ARGS(&raw_property_store));

	return SUCCEEDED(result);
}

unsigned int MetadataReadWrite::GetRating() const
{
	PROPVARIANT prop_value;
	PropVariantInit(&prop_value);
	
	HRESULT result = raw_property_store->GetValue(PKEY_Rating, &prop_value);
	if (SUCCEEDED(result))
	{
		return static_cast<unsigned int>(std::ceil(prop_value.lVal / 20.0)); // Convert from 0-100 to 0-5 scale
	}

	return 0;
}

void MetadataReadWrite::SetRating(const unsigned int rating)
{
	PROPVARIANT prop_value;
	PropVariantInit(&prop_value);
	prop_value.vt = VT_UI4;
	switch (rating)
	{
	case 0:
	    // Remove rating
	    prop_value.ulVal = 0;
	    break;
	case 1:
	    prop_value.ulVal = 12;
	    break;
	case 2:
	    prop_value.ulVal = 37;
	    break;
	case 3:
	    prop_value.ulVal = 59;
	    break;
	case 4:
	    prop_value.ulVal = 79;
	    break;
	case 5:
	    prop_value.ulVal = 99;
	    break;
	}

	HRESULT result = SetPropertyValueWithRetries(PKEY_Rating, prop_value);
	
	if (FAILED(result))
	{
        throw std::runtime_error("Failed to set rating");
    }
}

void MetadataReadWrite::RemoveRating()
{
	SetRating(0);
}

void MetadataReadWrite::SetTags(const std::vector<std::wstring>& tags)
{
	HRESULT result = E_FAIL;

	PROPVARIANT prop_value;
	PropVariantInit(&prop_value);
	prop_value.vt = VT_VECTOR | VT_LPWSTR;
	prop_value.calpwstr.cElems = static_cast<ULONG>(tags.size());

	// cgaarden is this correct -- do I need CoTaskMemAlloc here?
    prop_value.calpwstr.pElems = static_cast<LPWSTR*>(CoTaskMemAlloc(sizeof(LPWSTR) * tags.size()));
	for (ULONG i = 0; i < tags.size(); i++)
	{
        prop_value.calpwstr.pElems[i] = static_cast<LPWSTR>(CoTaskMemAlloc((tags[i].size() + 1) * sizeof(wchar_t)));
	    if (prop_value.calpwstr.pElems[i] != nullptr)
	    {
	        wcscpy_s(prop_value.calpwstr.pElems[i], tags[i].size() + 1, tags[i].c_str());
	    }
	}

	result = SetPropertyValueWithRetries(PKEY_Keywords, prop_value);
	
	if (FAILED(result))
	{
        throw std::runtime_error("Failed to set tags");
    }
}

std::vector<std::wstring> MetadataReadWrite::GetTags() const
{
    std::vector<std::wstring> tags;

    PROPVARIANT prop_value;
    PropVariantInit(&prop_value);

    HRESULT result = raw_property_store->GetValue(PKEY_Keywords, &prop_value);
    if (SUCCEEDED(result) && prop_value.vt == (VT_VECTOR | VT_LPWSTR)) 
	{
        for (ULONG i = 0; i < prop_value.calpwstr.cElems; i++) 
		{
            tags.push_back(prop_value.calpwstr.pElems[i]);
        }
    }
    return tags;
}

std::vector<std::wstring> MetadataReadWrite::GetSortedTags() const
{
    std::vector<std::wstring> tags;

    PROPVARIANT prop_value;
    PropVariantInit(&prop_value);

    HRESULT result = raw_property_store->GetValue(PKEY_Keywords, &prop_value);
    if (SUCCEEDED(result) && prop_value.vt == (VT_VECTOR | VT_LPWSTR))
    {
        for (ULONG i = 0; i < prop_value.calpwstr.cElems; i++)
        {
            // Insert tag in alphabetical order, case-insensitive
            auto ci_less = [](const std::wstring& a, const std::wstring& b) {
                return std::lexicographical_compare(
                    a.begin(), a.end(), b.begin(), b.end(), [](wchar_t ac, wchar_t bc) 
					{
                        return std::towlower(ac) < std::towlower(bc);
                    });
            };

            const std::wstring& new_tag = prop_value.calpwstr.pElems[i];
            auto iterator = std::lower_bound(tags.begin(), tags.end(), new_tag, ci_less);
            tags.insert(iterator, new_tag);
        }
    }
    return tags;
}

void MetadataReadWrite::AppendTags(const std::vector<std::wstring>& tags)
{
    std::vector<std::wstring> all_tags = GetTags();

    // Append new tags, avoiding duplicates
    for (const auto& tag : tags) 
	{
        if (std::find(all_tags.begin(), all_tags.end(), tag) == std::end(all_tags)) 
		{
            all_tags.push_back(tag);
        }
    }

    // Set the combined tags
    SetTags(all_tags);
}

void MetadataReadWrite::RemoveAllTags()
{
    PROPVARIANT prop_value;
    PropVariantInit(&prop_value);

    prop_value.vt = VT_VECTOR | VT_LPWSTR;
    prop_value.calpwstr.cElems = 0;
    prop_value.calpwstr.pElems = nullptr;

    HRESULT result = SetPropertyValueWithRetries(PKEY_Keywords, prop_value);

	if (FAILED(result))
    {
        throw std::runtime_error("Failed to remove all tags");
    }
}

void MetadataReadWrite::RemoveSpecifiedTags(const std::vector<std::wstring>& tags_to_remove)
{
    std::vector<std::wstring> all_tags = GetTags();

    // Remove tags
    for (const auto& tag : tags_to_remove)
    {
        auto iterator = std::find(all_tags.begin(), all_tags.end(), tag);

        if (iterator != std::end(all_tags))
        {
            all_tags.erase(iterator);
        }
    }

    // Set the combined tags
    SetTags(all_tags);
}

HRESULT MetadataReadWrite::SetPropertyValueWithRetries(REFPROPERTYKEY prop_key, REFPROPVARIANT prop_value)
{
    HRESULT result = E_FAIL;

    int number_of_retries = 0;

	// cgaarden UPDATE this to only retry on the correct set of failures
    while (number_of_retries < 3 && FAILED(result))
    {
        result = raw_property_store->SetValue(prop_key, prop_value);

        if (FAILED(result))
        {
            const std::chrono::milliseconds wait_a_bit{ 50 };
            std::this_thread::sleep_for(std::chrono::milliseconds(wait_a_bit));
        }
    }

	return result;
}

void MetadataReadWrite::WriteChanges()
{
    HRESULT result = E_FAIL;

    int number_of_retries = 0;

    // cgaarden UPDATE this to only retry on the correct set of failures
    while (number_of_retries < 3 && FAILED(result))
    {
        result = raw_property_store->Commit();

        if (FAILED(result))
        {
            const std::chrono::milliseconds wait_a_bit{ 50 };
            std::this_thread::sleep_for(std::chrono::milliseconds(wait_a_bit));
        }
    }

	if (FAILED(result))
	{
        throw std::runtime_error("Failed to commit changes to metadata.");
	}
}

void MetadataReadWrite::Close() noexcept
{
	if (raw_property_store)
	{
		raw_property_store->Release();
		raw_property_store = nullptr;
	}
}

