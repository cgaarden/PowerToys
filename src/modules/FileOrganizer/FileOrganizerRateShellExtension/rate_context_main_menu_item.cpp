#include "pch.h"

#include "rate_context_main_menu_item.h"
#include "rate_context_sub_menu_collection.h"
#include "rate_context_sub_menu_item.h"
#include "settings.h"
#include "trace.h"
#include "Generated Files/resource.h"

using namespace Microsoft::WRL;
using namespace file_organizer;

#pragma region IExplorerCommand
IFACEMETHODIMP rate_context_main_menu_item::GetTitle(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_title)
{
    static const std::wstring localized_context_menu_item_rate = 
        GET_RESOURCE_STRING_FALLBACK(IDS_CONTEXT_MENU_ITEM_RATE, L"Rate");
    return SHStrDup(localized_context_menu_item_rate.c_str(), returned_title);
}

IFACEMETHODIMP rate_context_main_menu_item::GetIcon(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_icon)
{
    *returned_icon = nullptr;
    static const auto icon_resource_filepath = utilities::get_rate_icon_resource_filepath(module_instance_handle, ThemeHelpers::GetAppTheme());
    return SHStrDup(icon_resource_filepath.c_str(), returned_icon);
}

IFACEMETHODIMP rate_context_main_menu_item::GetToolTip(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_tool_tip)
{
    *returned_tool_tip = nullptr;
    return E_NOTIMPL;
}

IFACEMETHODIMP rate_context_main_menu_item::GetCanonicalName(_Out_ GUID* returned_id)
{
    *returned_id = GUID_NULL;
    // __uuidof(this);
    return S_OK;
}

IFACEMETHODIMP rate_context_main_menu_item::GetState(_In_opt_ IShellItemArray*, _In_ BOOL, _Out_ EXPCMDSTATE* returned_state)
{
    if (!FileOrganizerSettingsInstance().GetRateEnabled())
    {
        *returned_state = ECS_HIDDEN;
    }
    else
    {
        *returned_state = ECS_ENABLED;
    }
    return S_OK;
}

IFACEMETHODIMP rate_context_main_menu_item::Invoke(_In_opt_ IShellItemArray*, _In_opt_ IBindCtx*) noexcept
{
    return E_NOTIMPL;
}

IFACEMETHODIMP rate_context_main_menu_item::GetFlags(_Out_ EXPCMDFLAGS* returned_menu_item_flags)
{
    *returned_menu_item_flags = ECF_HASSUBCOMMANDS;
    return S_OK;
}

IFACEMETHODIMP rate_context_main_menu_item::EnumSubCommands(_COM_Outptr_ IEnumExplorerCommand** returned_enum_commands)
{
    auto e = Make<rate_context_sub_menu_collection>(site_of_folder);
    return e->QueryInterface(IID_PPV_ARGS(returned_enum_commands));
}
#pragma endregion

#pragma region IObjectWithSite
IFACEMETHODIMP rate_context_main_menu_item::SetSite(_In_ IUnknown* site) noexcept
{
    site_of_folder = site;
    return S_OK;
}

IFACEMETHODIMP rate_context_main_menu_item::GetSite(_In_ REFIID riid, _COM_Outptr_ void** returned_site) noexcept
{
    return site_of_folder.CopyTo(riid, returned_site);
}
#pragma endregion
