#include "pch.h"
#include "tag_context_sub_menu_collection.h"
#include "tag_context_sub_menu_item.h"
#include "trace.h"
#include "utilities.h"

using namespace Microsoft::WRL;

// // Sub context menu command enumerator
tag_context_sub_menu_collection::tag_context_sub_menu_collection(const ComPtr<IUnknown> site_of_folder)
{
    this->site_of_folder = site_of_folder;

    // cgaarden

    // Add items to context menu
    explorer_menu_item_commands.push_back(Make<tag_context_sub_menu_item>(
        site_of_folder, 
        L"Blue", 
        file_organizer::utilities::get_tag_icon_number_resource_filepath(L"1", file_organizer::utilities::tagged),
        ECS_CHECKED));

    explorer_menu_item_commands.push_back(Make<tag_context_sub_menu_item>(
        site_of_folder,
        L"Light blue",
        file_organizer::utilities::get_tag_icon_number_resource_filepath(L"2", file_organizer::utilities::tagged),
        ECS_CHECKBOX));

    explorer_menu_item_commands.push_back(Make<tag_context_sub_menu_item>(
        site_of_folder,
        L"Green",
        file_organizer::utilities::get_tag_icon_number_resource_filepath(L"3")));

    explorer_menu_item_commands.push_back(Make<tag_context_sub_menu_item>(
        site_of_folder,
        L"Light green",
        file_organizer::utilities::get_tag_icon_number_resource_filepath(L"4")));

    explorer_menu_item_commands.push_back(Make<tag_context_sub_menu_item>(
        site_of_folder,
        L"Renamed category 1",
        file_organizer::utilities::get_tag_icon_number_resource_filepath(L"5")));

    explorer_menu_item_commands.push_back(Make<tag_context_sub_menu_item>(
        site_of_folder,
        L"Renamed category 2",
        file_organizer::utilities::get_tag_icon_number_resource_filepath(L"6")));

    explorer_menu_item_commands.push_back(Make<tag_context_sub_menu_item>(
        site_of_folder,
        L"Renamed category 3",
        file_organizer::utilities::get_tag_icon_number_resource_filepath(L"7")));

    explorer_menu_item_commands.push_back(Make<tag_context_sub_menu_item>(
        site_of_folder,
        L"Renamed category 4",
        file_organizer::utilities::get_tag_icon_number_resource_filepath(L"8")));

    explorer_menu_item_commands.push_back(Make<tag_context_sub_menu_item>(
        site_of_folder,
        L"Renamed category 5",
        file_organizer::utilities::get_tag_icon_number_resource_filepath(L"9")));

    // Add "All tags" item to context menu
    explorer_menu_item_commands.push_back(Make<all_tags_context_menu_item>());

    // Add "Remove all tags" item to context menu
    explorer_menu_item_commands.push_back(Make<remove_all_tags_context_menu_item>());

    // Add separator to context menu
    explorer_menu_item_commands.push_back(Make<separator_context_menu_item>());

    // Add "Manage tags" item to context menu
    explorer_menu_item_commands.push_back(Make<manage_tags_context_menu_item>());

    current_command = explorer_menu_item_commands.cbegin();
}

// IEnumExplorerCommand
IFACEMETHODIMP tag_context_sub_menu_collection::Next(ULONG celt, __out_ecount_part(celt, *pceltFetched) IExplorerCommand** apUICommand, __out_opt ULONG* pceltFetched)
{
    ULONG fetched{ 0 };

    if (pceltFetched)
    {
        *pceltFetched = 0ul;
    }

    for (ULONG i = 0; (i < celt) && (current_command != explorer_menu_item_commands.cend()); i++)
    {
        current_command->CopyTo(&apUICommand[0]);
        current_command++;
        fetched++;
    }

    if (pceltFetched)
    {
        *pceltFetched = fetched;
    }

    return (fetched == celt) ? S_OK : S_FALSE;
}

IFACEMETHODIMP tag_context_sub_menu_collection::Skip(ULONG)
{
    return E_NOTIMPL;
}
IFACEMETHODIMP tag_context_sub_menu_collection::Reset()
{
    current_command = explorer_menu_item_commands.cbegin();
    return S_OK;
}
IFACEMETHODIMP tag_context_sub_menu_collection::Clone(__deref_out IEnumExplorerCommand** ppenum)
{
    *ppenum = nullptr;
    return E_NOTIMPL;
}
