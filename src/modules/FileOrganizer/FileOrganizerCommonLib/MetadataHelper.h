#pragma once
#include <string>
#include <vector>

class MetadataHelper 
{
public:
    static unsigned int GetFileRating(const std::wstring& file_path);
    static std::pair<double, bool> GetAverageRatingAndUniformFlag(const std::vector<std::wstring>& file_paths);
};
