#include "pch.h"
#include "MetadataHelper.h"
#include "Metadata.h"

unsigned int MetadataHelper::GetFileRating(const std::wstring& file_path) 
{
    MetadataReadWrite metadata;
    metadata.Open(file_path);
    const unsigned int rating = metadata.GetRating();
    return rating;
}

std::pair<double, bool> MetadataHelper::GetAverageRatingAndUniformFlag(const std::vector<std::wstring>& file_paths)
{
    size_t count = 0;
    double sum = 0.0;
    bool all_same = true;
    unsigned int first_rating = 0;
    bool first = true;

    for (const auto& file_path : file_paths)
    {
        if (count >= 50)
        {
            // More than 50 files, assume they are all the same
			all_same = false;
            break;
        }
        MetadataReadWrite metadata;
        metadata.Open(file_path);
        const unsigned int rating = metadata.GetRating();
        if (first)
        {
            first_rating = rating;
            first = false;
        }
        else if (rating != first_rating)
        {
            all_same = false;
        }
        sum += rating;
        ++count;
    }

    const double average_rating = (count > 0) ? (sum / count) : 0.0;
    return { average_rating, all_same };
}
