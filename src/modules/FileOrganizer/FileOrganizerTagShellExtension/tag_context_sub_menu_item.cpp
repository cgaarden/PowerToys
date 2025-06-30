#include "pch.h"
#include "tag_context_sub_menu_item.h"

#include "trace.h"
#include "Generated Files/resource.h"
#include "utilities.h"
#include <FileOrganizer/FileOrganizerCommonLib/MetadataHelper.h>
#include <FileOrganizer/FileOrganizerCommonLib/shared_utilities.h>

using namespace Microsoft::WRL;

// Sub context menu containing the actual list of templates
tag_context_sub_menu_item::tag_context_sub_menu_item()
{
    this->site_of_folder = nullptr;
    this->state = ECS_ENABLED;
}

tag_context_sub_menu_item::tag_context_sub_menu_item(const ComPtr<IUnknown> site_of_folder, std::wstring title, std::wstring icon_path, EXPCMDSTATE state)
{
    this->site_of_folder = site_of_folder;
    this->title = title;
    this->icon_path = icon_path;
    this->state = state;
}

IFACEMETHODIMP tag_context_sub_menu_item::GetTitle(_In_opt_ IShellItemArray* items, _Outptr_result_nullonfailure_ PWSTR* returned_title)
{
    return SHStrDup(title.c_str(), returned_title);
}

IFACEMETHODIMP tag_context_sub_menu_item::GetIcon(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_icon)
{
    *returned_icon = nullptr;
    return SHStrDup(icon_path.c_str(), returned_icon);
}

IFACEMETHODIMP tag_context_sub_menu_item::GetToolTip(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_info_tip)
{
    *returned_info_tip = nullptr;
    return E_NOTIMPL;
}
IFACEMETHODIMP tag_context_sub_menu_item::GetCanonicalName(_Out_ GUID* guidCommandName)
{
    *guidCommandName = GUID_NULL;
    return S_OK;
}
IFACEMETHODIMP tag_context_sub_menu_item::GetState(_In_opt_ IShellItemArray* selection, _In_ BOOL, _Out_ EXPCMDSTATE* returned_state)
{
    *returned_state = state;
    return S_OK;
}

IFACEMETHODIMP tag_context_sub_menu_item::Invoke(_In_opt_ IShellItemArray* selection, _In_opt_ IBindCtx*) noexcept
{
    DWORD item_count = 0;
    selection->GetCount(&item_count);
    try
    {
        const auto file_paths = file_organizer::shared_utilities::GetFilePathsFromShellItemArray(selection);

        // Append tag for all selected files
        MetadataHelper::AppendTagsForMultipleFiles(file_paths, { this->title });

        // Refresh the file explorer shell to reflect the changes
        file_organizer::shared_utilities::RefreshShellForMultipleFiles(file_paths);
    }
    catch (std::exception& e)
    {
        Logger::error("Failed to append tags for files: {}", std::string{ e.what() });
        return E_FAIL;
    }
    catch (...)
    {
        Logger::error("Failed to append tags for selected files...");
        return E_FAIL;
    }

    return S_OK;
}

IFACEMETHODIMP tag_context_sub_menu_item::GetFlags(_Out_ EXPCMDFLAGS* returned_flags)
{
    *returned_flags = ECF_HIDELABEL;
    return S_OK;
}

IFACEMETHODIMP tag_context_sub_menu_item::EnumSubCommands(_COM_Outptr_ IEnumExplorerCommand** enumCommands)
{
    *enumCommands = nullptr;
    return E_NOTIMPL;
}

// Sub context menu - separator
IFACEMETHODIMP separator_context_menu_item::GetTitle(_In_opt_ IShellItemArray* items, _Outptr_result_nullonfailure_ PWSTR* returned_title)
{
    returned_title = nullptr;

    // NOTE: Must by S_FALSE for the separator to show up
    return S_FALSE;
}

IFACEMETHODIMP separator_context_menu_item::GetIcon(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_icon)
{
    *returned_icon = nullptr;
    return E_NOTIMPL;
}

IFACEMETHODIMP separator_context_menu_item::GetState(_In_opt_ IShellItemArray* selection, _In_ BOOL, _Out_ EXPCMDSTATE* returned_state)
{
    *returned_state = ECS_DISABLED;
    return S_OK;
}

IFACEMETHODIMP separator_context_menu_item::GetFlags(_Out_ EXPCMDFLAGS* returned_flags)
{
    *returned_flags = ECF_ISSEPARATOR;
    return S_OK;
}

// ----------------------------------------------------------------------
// Sub context menu - "All tags"
// ----------------------------------------------------------------------
IFACEMETHODIMP all_tags_context_menu_item::GetTitle(_In_opt_ IShellItemArray* items, _Outptr_result_nullonfailure_ PWSTR* returned_title)
{
    static const std::wstring localized_context_menu_item =
        GET_RESOURCE_STRING_FALLBACK(IDS_CONTEXT_MENU_ITEM_ALL_TAGS, L"All tags");
    return SHStrDup(localized_context_menu_item.c_str(), returned_title);
}

IFACEMETHODIMP all_tags_context_menu_item::GetIcon(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_icon)
{
    *returned_icon = nullptr;
    return E_NOTIMPL;
}

IFACEMETHODIMP all_tags_context_menu_item::Invoke(_In_opt_ IShellItemArray* selection, _In_opt_ IBindCtx*) noexcept
{
    return E_NOTIMPL;
}

// ----------------------------------------------------------------------
// Sub context menu - "Remove all tags"
// ----------------------------------------------------------------------
IFACEMETHODIMP remove_all_tags_context_menu_item::GetTitle(_In_opt_ IShellItemArray* items, _Outptr_result_nullonfailure_ PWSTR* returned_title)
{
    static const std::wstring localized_context_menu_item =
        GET_RESOURCE_STRING_FALLBACK(IDS_CONTEXT_MENU_ITEM_REMOVE_ALL_TAGS, L"Remove all tags");
    return SHStrDup(localized_context_menu_item.c_str(), returned_title);
}

IFACEMETHODIMP remove_all_tags_context_menu_item::GetIcon(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_icon)
{
    *returned_icon = nullptr;
    return E_NOTIMPL;
}

IFACEMETHODIMP remove_all_tags_context_menu_item::Invoke(_In_opt_ IShellItemArray* selection, _In_opt_ IBindCtx*) noexcept
{
    DWORD item_count = 0;
    selection->GetCount(&item_count);
    try
    {
        const auto file_paths = file_organizer::shared_utilities::GetFilePathsFromShellItemArray(selection);

        RemoveAllTags(file_paths);
    }
    catch (std::exception& e)
    {
        Logger::error("Failed to remove tags for files: {}", std::string{ e.what() });
        return E_FAIL;
    }
    catch (...)
    {
        Logger::error("Failed to remove tags for selected files...");
        return E_FAIL;
    }

    return S_OK;
}


void remove_all_tags_context_menu_item::RemoveAllTags(const std::vector<std::wstring>& file_paths) const
{
    std::thread thread_for_renaming_workaround(RemoveAllTagsOnOtherThread, file_paths);
    thread_for_renaming_workaround.detach();
}

void remove_all_tags_context_menu_item::RemoveAllTagsOnOtherThread(const std::vector<std::wstring>& file_paths)
{
    // Remove all tags for all selected files
    MetadataHelper::RemoveAllTagsForMultipleFiles(file_paths);

    // Refresh the file explorer shell to reflect the changes
    file_organizer::shared_utilities::RefreshShellForMultipleFiles(file_paths);
}


// ----------------------------------------------------------------------
// Sub context menu - "Manage tags"
// ----------------------------------------------------------------------
IFACEMETHODIMP manage_tags_context_menu_item::GetTitle(_In_opt_ IShellItemArray* items, _Outptr_result_nullonfailure_ PWSTR* returned_title)
{
    static const std::wstring localized_context_menu_item =
        GET_RESOURCE_STRING_FALLBACK(IDS_CONTEXT_MENU_ITEM_MANAGE_TAGS, L"Manage tags");
    return SHStrDup(localized_context_menu_item.c_str(), returned_title);
}

IFACEMETHODIMP manage_tags_context_menu_item::GetIcon(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_icon)
{
    *returned_icon = nullptr;
    return E_NOTIMPL;
}

IFACEMETHODIMP manage_tags_context_menu_item::Invoke(_In_opt_ IShellItemArray* selection, _In_opt_ IBindCtx*) noexcept
{
    return E_NOTIMPL;
}


