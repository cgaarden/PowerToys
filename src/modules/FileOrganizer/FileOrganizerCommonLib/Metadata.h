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
	~MetadataReadWrite();
	void Open(const std::wstring& file_path);
	unsigned int GetRating() const;
	void SetRating(const unsigned int rating);
	void RemoveRating();
	std::vector<std::wstring> GetTags() const;
	void SetTags(const std::vector<std::wstring>& tags);
	void AppendTags(const std::vector<std::wstring>& tags);
	void WriteChanges();
	void Close();

protected:
	IPropertyStore* raw_property_store; // Ensure IPropertyStore is defined
};

