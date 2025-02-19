#include "pch.h"
#include "rate_context_sub_menu_item.h"

#include "trace.h"
#include "Generated Files/resource.h"
#include "utilities.h"

using namespace Microsoft::WRL;

// Sub context menu containing the actual list of templates
rate_context_sub_menu_item::rate_context_sub_menu_item(const ComPtr<IUnknown> site_of_folder, std::wstring title, EXPCMDSTATE menu_item_state)
{
    this->site_of_folder = site_of_folder;
    this->title = title;
    this->menu_item_state = menu_item_state;
}

IFACEMETHODIMP rate_context_sub_menu_item::GetTitle(_In_opt_ IShellItemArray* items, _Outptr_result_nullonfailure_ PWSTR* returned_title)
{
    return SHStrDup(title.c_str(), returned_title);
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

IFACEMETHODIMP rate_context_sub_menu_item::Invoke(_In_opt_ IShellItemArray*, _In_opt_ IBindCtx*) noexcept
{
    return E_NOTIMPL;
    //return newplus::utilities::copy_template(template_entry, site_of_folder);
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

