#include "pch.h"
#include "rate_context_sub_menu_collection.h"
#include "rate_context_sub_menu_item.h"
#include "trace.h"
#include "utilities.h"

using namespace Microsoft::WRL;

// // Sub context menu command enumerator
rate_context_sub_menu_collection::rate_context_sub_menu_collection(const ComPtr<IUnknown> site_of_folder)
{
    this->site_of_folder = site_of_folder;

    // cgaarden hack for spec...

    // Add Rating items to context menu
    // ⭐ ☆ ★
    explorer_menu_item_commands.push_back(Make<rate_context_sub_menu_item>(site_of_folder, L"☆"));
    explorer_menu_item_commands.push_back(Make<rate_context_sub_menu_item>(site_of_folder, L"☆☆"));
    explorer_menu_item_commands.push_back(Make<rate_context_sub_menu_item>(site_of_folder, L"☆☆☆"));
    explorer_menu_item_commands.push_back(Make<rate_context_sub_menu_item>(site_of_folder, L"★★★★"));
    explorer_menu_item_commands.push_back(Make<rate_context_sub_menu_item>(site_of_folder, L"☆☆☆☆☆"));
    explorer_menu_item_commands.push_back(Make<rate_context_sub_menu_item>(site_of_folder, L"Remove rating"));

    current_command = explorer_menu_item_commands.cbegin();
}

// IEnumExplorerCommand
IFACEMETHODIMP rate_context_sub_menu_collection::Next(ULONG celt, __out_ecount_part(celt, *pceltFetched) IExplorerCommand** apUICommand, __out_opt ULONG* pceltFetched)
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

IFACEMETHODIMP rate_context_sub_menu_collection::Skip(ULONG)
{
    return E_NOTIMPL;
}
IFACEMETHODIMP rate_context_sub_menu_collection::Reset()
{
    current_command = explorer_menu_item_commands.cbegin();
    return S_OK;
}
IFACEMETHODIMP rate_context_sub_menu_collection::Clone(__deref_out IEnumExplorerCommand** returned_enum_not_used)
{
    *returned_enum_not_used = nullptr;
    return E_NOTIMPL;
}
