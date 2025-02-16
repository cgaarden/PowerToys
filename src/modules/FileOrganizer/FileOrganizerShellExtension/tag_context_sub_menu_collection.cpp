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
    explorer_menu_item_commands.push_back(Make<tag_context_sub_menu_item>(site_of_folder));
    explorer_menu_item_commands.push_back(Make<tag_context_sub_menu_item>(site_of_folder));
    explorer_menu_item_commands.push_back(Make<tag_context_sub_menu_item>(site_of_folder));

    // Add separator to context menu
    // explorer_menu_item_commands.push_back(Make<separator_context_menu_item>());

    // Add "Manage tags" item to context menu
    // explorer_menu_item_commands.push_back(Make<template_folder_context_menu_item>(root));

    current_command = explorer_menu_item_commands.cbegin();

    // Save how many item templates we have so it can be sent later when we do something with New+.
    // We don't send it here or it would send an event every time we open a context menu.
//    newplus::utilities::set_saved_number_of_templates(static_cast<size_t>(number_of_templates));
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
