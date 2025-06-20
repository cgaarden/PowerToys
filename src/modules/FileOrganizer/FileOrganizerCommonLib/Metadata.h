#pragma once
#include <string>
#include <vector>
#include <propsys.h>

struct MetaData
{
	std::wstring file_path;
	std::vector<std::wstring> tags;
	unsigned int rating;
};

class MetadataReadWrite
{
public:
	// General metadata 
	~MetadataReadWrite();
    bool Open(const std::wstring& file_path) noexcept;
	void WriteChanges();
	void Close() noexcept;

	// Rating related
	unsigned int GetRating() const;
	void SetRating(const unsigned int rating);
	void RemoveRating();

	// Tagging related
	std::vector<std::wstring> GetTags() const;
    std::vector<std::wstring> GetSortedTags() const;
    void SetTags(const std::vector<std::wstring>& tags);
	void AppendTags(const std::vector<std::wstring>& tags);
    void RemoveAllTags();

protected:
	IPropertyStore* raw_property_store; // Ensure IPropertyStore is defined
};

