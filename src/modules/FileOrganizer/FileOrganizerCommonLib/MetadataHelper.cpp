#include "pch.h"
#include "MetadataHelper.h"
#include "Metadata.h"
#include <common/logger/logger.h>
#include <ShlObj.h>
#include "shared_utilities.h"

unsigned int MetadataHelper::GetFileRating(const std::wstring& file_path) 
{
    MetadataReadWrite metadata;
    unsigned int rating = 0;
    if (metadata.Open(file_path))
    {
        rating = metadata.GetRating();
    }
    return rating;
}

std::pair<bool, unsigned int> MetadataHelper::GetRatingUniformityAndFirstRating(const std::vector<std::wstring>& file_paths)
{
    size_t count = 0;
    bool all_same = true;
    unsigned int first_rating = 0;
    bool first = true;

    for (const auto& file_path : file_paths)
    {
        try
        {
            MetadataReadWrite metadata;
            if (metadata.Open(file_path))
            {
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
                ++count;
            }

            if (count >= 50)
            {
                // More than 50 files, assume they are all different
                all_same = false;
                break;
            }
        }
        catch (...)
        {
            throw std::runtime_error("Error while getting the rating for file");
        }
    }

    return { all_same, first_rating };
}

void MetadataHelper::SetRatingForMultipleFiles(const std::vector<std::wstring>& file_paths, const unsigned int rating)
{
    for (const auto& file_path : file_paths)
    {
        try
        {
            MetadataReadWrite metadata;
            if (metadata.Open(file_path))
            {
                metadata.SetRating(rating);
                metadata.WriteChanges();
                metadata.Close();
            }
        }
        catch (...)
        {
            throw std::runtime_error("Error while setting the rating for file");
        }
    }
}

void MetadataHelper::RemoveRatingForMultipleFiles(const std::vector<std::wstring>& file_paths)
{
    for (const auto& file_path : file_paths)
    {
        try
        {
            MetadataReadWrite metadata;
            if (metadata.Open(file_path))
            {
                metadata.RemoveRating();
                metadata.WriteChanges();
                metadata.Close();
            }
        }
        catch (...)
        {
            throw std::runtime_error("Error while removing rating from file");
        }
    }
}

std::pair<bool, std::vector<std::wstring>> MetadataHelper::GetTagsUniformityAndTagsFromFirstFile(const std::vector<std::wstring>& file_paths)
{
    // cgaarden REMOVE THIS method
    bool all_same = true;
    std::vector<std::wstring> first_tags;
    bool first = true;

    for (const auto& file_path : file_paths)
    {
        try
        {
            MetadataReadWrite metadata;
            if (metadata.Open(file_path))
            {
                const std::vector<std::wstring>& tags = metadata.GetSortedTags();
                if (first)
                {
                    first_tags = tags;
                    first = false;
                }
                else if (tags.size() != first_tags.size() || !std::equal(tags.begin(), tags.end(), first_tags.begin()))
                {
                    all_same = false;
                    break;
                }
            }

            if (file_paths.size() >= 50)
            {
                // More than 50 files, assume they are all different
                all_same = false;
                break;
            }
        }
        catch (...)
        {
            throw std::runtime_error("Error while getting the tags for file");
        }
    }

    return { all_same, first_tags };
}

void MetadataHelper::AppendTagsForMultipleFiles(const std::vector<std::wstring>& file_paths, const std::vector<std::wstring>& tags_to_append)
{
    for (const auto& file_path : file_paths)
    {
        try
        {
            MetadataReadWrite metadata;
            if (metadata.Open(file_path))
            {
                metadata.AppendTags(tags_to_append);
                metadata.WriteChanges();
                metadata.Close();
                // file_organizer::shared_utilities::RefreshShellForMultipleFiles({ file_path });
            }
        }
        catch (...)
        {
            throw std::runtime_error("Error while appending tags to file");
        }
    }
}

void MetadataHelper::RemoveAllTagsForMultipleFiles(const std::vector<std::wstring>& file_paths)
{
    for (const auto& file_path : file_paths)
    {
        try
        {
            MetadataReadWrite metadata;
            if (metadata.Open(file_path))
            {
                metadata.RemoveAllTags();
                metadata.WriteChanges();
                metadata.Close();
                // file_organizer::shared_utilities::RefreshShellForMultipleFiles({ file_path });
            }
        }
        catch (std::exception& e)
        {
            throw std::runtime_error(std::format("Error while removing all tags from file: {}", std::string{ e.what() }));
        }
        catch (...)
        {
            throw std::runtime_error("Error while removing all tags from file");
        }
    }
}

std::vector<std::wstring> MetadataHelper::GetSharedTagsForMultipleFiles(const std::vector<std::wstring>& file_paths)
{
    std::vector<std::wstring> shared_tags;
    bool first = true;

    for (const auto& file_path : file_paths)
    {
        try
        {
            if (file_paths.size() >= 50)
            {
                // More than 50 files, assume they are all different
                break;
            }

            MetadataReadWrite metadata;
            if (metadata.Open(file_path))
            {
                const std::vector<std::wstring>& tags = metadata.GetSortedTags();
                if (first)
                {
                    shared_tags = tags;
                    first = false;
                    continue;
                }

                for (auto shared_tags_it = shared_tags.begin(); shared_tags_it != std::end(shared_tags); shared_tags_it++)
                {
                    auto current_tags_it = std::find(tags.begin(), tags.end(), *shared_tags_it);

                    if (current_tags_it == std::end(tags))
                    {
                        shared_tags.erase(shared_tags_it);
                        shared_tags_it = shared_tags.begin();
                    }
                }
            }
        }
        catch (...)
        {
            throw std::runtime_error("Error while getting the tags for file");
        }
    }

    return shared_tags;
}

void MetadataHelper::RemoveSpecificTagsForMultipleFiles(const std::vector<std::wstring>& file_paths, const std::vector<std::wstring>& tags_to_remove)
{
    for (const auto& file_path : file_paths)
    {
        try
        {
            MetadataReadWrite metadata;
            if (metadata.Open(file_path))
            {
                metadata.RemoveSpecifiedTags(tags_to_remove);
                metadata.WriteChanges();
                metadata.Close();
            }
        }
        catch (...)
        {
            throw std::runtime_error("Error while removing specified tags from file");
        }
    }
}

