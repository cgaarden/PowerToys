#pragma once
#include <string>
#include <vector>

class MetadataHelper 
{
public:
    // Ratings related
    static unsigned int GetFileRating(const std::wstring& file_path);
    static std::pair<bool, unsigned int> GetRatingUniformityAndFirstRating(const std::vector<std::wstring>& file_paths);
    static void SetRatingForMultipleFiles(const std::vector<std::wstring>& file_paths, const unsigned int rating);
    static void RemoveRatingForMultipleFiles(const std::vector<std::wstring>& file_paths);

    // Tags related
    static std::pair<bool, std::vector<std::wstring>> GetTagsUniformityAndTagsFromFirstFile(const std::vector<std::wstring>& file_paths);
    static void AppendTagsForMultipleFiles(const std::vector<std::wstring>& file_paths, const std::vector<std::wstring>& tags_to_append);
    static void RemoveAllTagsForMultipleFiles(const std::vector<std::wstring>& file_paths);
    static std::vector<std::wstring> GetSharedTagsForMultipleFiles(const std::vector<std::wstring>& file_paths);
    static void RemoveSpecificTagsForMultipleFiles(const std::vector<std::wstring>& file_paths, const std::vector<std::wstring>& tags_to_remove);
};
