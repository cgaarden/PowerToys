#include "pch.h"
#include "Metadata.h"
#include <ShlObj.h>
#include <memory>
#include <propkey.h>
#include <cmath>

MetadataReadWrite::~MetadataReadWrite()
{
	Close();
}

void MetadataReadWrite::Open(const std::wstring& file_path)
{
	HRESULT result = SHGetPropertyStoreFromParsingName(file_path.c_str(), NULL, GPS_READWRITE, IID_PPV_ARGS(&raw_property_store));
	if (FAILED(result))
	{
	    return;
	}
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

	HRESULT result = raw_property_store->SetValue(PKEY_Rating, prop_value);
	
	if (FAILED(result))
	{
	    // cgaarden Log the error
	    return;
	}
}

void MetadataReadWrite::RemoveRating()
{
	SetRating(0);
}

void MetadataReadWrite::SetTags(const std::vector<std::wstring>& tags)
{
	HRESULT result = S_FALSE;

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
	result = raw_property_store->SetValue(PKEY_Keywords, prop_value);
	
	if (FAILED(result))
	{
	    // cgaarden Log the error
	    return;
	}
}

std::vector<std::wstring> MetadataReadWrite::GetTags() const
{
    std::vector<std::wstring> tags;
	if (!raw_property_store) 
	{
		return tags;
	}

    PROPVARIANT prop_value;
    PropVariantInit(&prop_value);

    HRESULT result = raw_property_store->GetValue(PKEY_Keywords, &prop_value);
    if (SUCCEEDED(result) && prop_value.vt == (VT_VECTOR | VT_LPWSTR)) {
        for (ULONG i = 0; i < prop_value.calpwstr.cElems; i++) {
            tags.push_back(prop_value.calpwstr.pElems[i]);
        }
    }
    return tags;
}

void MetadataReadWrite::AppendTags(const std::vector<std::wstring>& tags)
{
    if (!raw_property_store) 
	{
		return;
	}

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

void MetadataReadWrite::WriteChanges()
{
	HRESULT result = S_FALSE;

	if (raw_property_store)
	{
		result = raw_property_store->Commit();
	}

	if (FAILED(result))
	{
		// cgaarden Log the error
		return;
	}
}

void MetadataReadWrite::Close()
{
	if (raw_property_store)
	{
		raw_property_store->Release();
		raw_property_store = nullptr;
	}
}

