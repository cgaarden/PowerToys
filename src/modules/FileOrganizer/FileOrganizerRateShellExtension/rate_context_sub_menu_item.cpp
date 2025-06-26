#include "pch.h"  
#include "rate_context_sub_menu_item.h"  
#include "trace.h"  
#include "Generated Files/resource.h"  
#include "utilities.h"  
#include "..\FileOrganizerCommonLib\MetadataHelper.h"
#include <FileOrganizer/FileOrganizerCommonLib/shared_utilities.h>

using namespace Microsoft::WRL;  

rate_context_sub_menu_item::rate_context_sub_menu_item(const ComPtr<IUnknown> site_of_object, unsigned int rate, std::wstring title, EXPCMDSTATE menu_item_state)
{  
    this->site_of_object = site_of_object;  
    this->rate = rate;
    this->title = title;  
    this->menu_item_state = menu_item_state;
}  

IFACEMETHODIMP rate_context_sub_menu_item::GetTitle(_In_opt_ IShellItemArray* selection, _Outptr_result_nullonfailure_ PWSTR* returned_title)
{  
    std::wstring assumed_rate = title;

    DWORD item_count = 0;
    selection->GetCount(&item_count);

    try
    {
        // If rating is 0 or separator exit
        if (this->rate == 0)
        {
            return SHStrDup(title.c_str(), returned_title);
        }

        const auto file_paths = file_organizer::shared_utilities::GetFilePathsFromShellItemArray(selection);

        // Get the rating for all selected files
        const std::pair<bool, unsigned int> rating_result = MetadataHelper::GetRatingUniformityAndFirstRating(file_paths);
        const bool ratings_are_uniform = rating_result.first;
        const unsigned int first_rating = rating_result.second;

        if (ratings_are_uniform && this->rate == first_rating)
        {
            const std::wstring rating_string = file_organizer::utilities::get_solid_rate_as_string(first_rating);
            return SHStrDup(rating_string.c_str(), returned_title);
        }

        return SHStrDup(title.c_str(), returned_title);
    }
    catch (std::exception& e)
    {
        Logger::error("Failed to obtain rating for files: {}", std::string{ e.what() });
        return E_FAIL;
    }
    catch (...)
    {
        Logger::error("Failed to obtain rating for selected files...");
        return E_FAIL;
    }
    return E_FAIL;
}  

IFACEMETHODIMP rate_context_sub_menu_item::GetIcon(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_icon)  
{  
    *returned_icon = nullptr;  
    return E_NOTIMPL;  
}  

IFACEMETHODIMP rate_context_sub_menu_item::GetToolTip(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_info_tip)  
{  
    *returned_info_tip = nullptr;  
    return E_NOTIMPL;  
}  
IFACEMETHODIMP rate_context_sub_menu_item::GetCanonicalName(_Out_ GUID* guidCommandName)  
{  
    *guidCommandName = GUID_NULL;  
    return S_OK;  
}  
IFACEMETHODIMP rate_context_sub_menu_item::GetState(_In_opt_ IShellItemArray* selection, _In_ BOOL, _Out_ EXPCMDSTATE* returned_state)  
{  
    *returned_state = menu_item_state;  
    return S_OK;  
}  

IFACEMETHODIMP rate_context_sub_menu_item::Invoke(_In_opt_ IShellItemArray* selection, _In_opt_ IBindCtx*) noexcept
{  
    DWORD item_count = 0;
    selection->GetCount(&item_count);
    try
    {
        std::vector<std::wstring> file_paths;

        // For each selected shell item, get their file paths
        for (DWORD i = 0; i < item_count; i++)
        {
            CComPtr<IShellItem> shell_item;
            if (SUCCEEDED(selection->GetItemAt(i, &shell_item)))
            {
                PWSTR file_path = nullptr;
                if (SUCCEEDED(shell_item->GetDisplayName(SIGDN_FILESYSPATH, &file_path)))
                {
                    file_paths.push_back(file_path);
                    CoTaskMemFree(file_path);
                }
            }
        }

        // Set the rating for all selected files
        MetadataHelper::SetRatingForMultipleFiles(file_paths, rate);

        // Refresh the file explorer shell to reflect the changes
        file_organizer::shared_utilities::RefreshShellForMultipleFiles(file_paths);
    }
    catch (std::exception& e)
    {
        Logger::error("Failed to set rating for files: {}", std::string{ e.what() });
        return E_FAIL;
    }
    catch (...)
    {
        Logger::error("Failed to set rating for selected files...");
        return E_FAIL;
    }

    return S_OK;
}  

IFACEMETHODIMP rate_context_sub_menu_item::GetFlags(_Out_ EXPCMDFLAGS* returned_flags)  
{  
    *returned_flags = ECF_DEFAULT;  
    return S_OK;  
}  

IFACEMETHODIMP rate_context_sub_menu_item::EnumSubCommands(_COM_Outptr_ IEnumExplorerCommand** enumCommands)  
{  
    *enumCommands = nullptr;  
    return E_NOTIMPL;  
}  

// ------------------------------------------------------------------  
// Sub context menu - separator  
// ------------------------------------------------------------------  
IFACEMETHODIMP rate_separator_context_menu_item::GetTitle(_In_opt_ IShellItemArray* items, _Outptr_result_nullonfailure_ PWSTR* returned_title)  
{  
    returned_title = nullptr;  

    // NOTE: Must by S_FALSE for the separator to show up  
    return S_FALSE;  
}  

IFACEMETHODIMP rate_separator_context_menu_item::GetIcon(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_icon)  
{  
    *returned_icon = nullptr;  
    return E_NOTIMPL;  
}  

IFACEMETHODIMP rate_separator_context_menu_item::GetState(_In_opt_ IShellItemArray* selection, _In_ BOOL, _Out_ EXPCMDSTATE* returned_state)  
{  
    *returned_state = ECS_DISABLED;  
    return S_OK;  
}  

IFACEMETHODIMP rate_separator_context_menu_item::GetFlags(_Out_ EXPCMDFLAGS* returned_flags)  
{  
    *returned_flags = ECF_ISSEPARATOR;  
    return S_OK;  
}
