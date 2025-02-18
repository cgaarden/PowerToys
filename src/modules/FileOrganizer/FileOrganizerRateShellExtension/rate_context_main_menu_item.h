#pragma once

#include "pch.h"

using namespace Microsoft::WRL;

#define FILE_ORGANIZER_SHELL_EXTENSION_RATE_EXPLORER_COMMAND_UUID_STR "DF9672B2-B7C8-49F8-AE48-054B361C1448"

// File Explorer context menu "Rate"
class __declspec(uuid(FILE_ORGANIZER_SHELL_EXTENSION_RATE_EXPLORER_COMMAND_UUID_STR)) rate_context_main_menu_item final :
    public RuntimeClass<
        RuntimeClassFlags<ClassicCom>,
        IExplorerCommand,
        IObjectWithSite>
{
public:
#pragma region IExplorerCommand
    IFACEMETHODIMP GetTitle(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_title);
    IFACEMETHODIMP GetIcon(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_icon);
    IFACEMETHODIMP GetToolTip(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_tool_tip);
    IFACEMETHODIMP GetCanonicalName(_Out_ GUID* returned_id);
    IFACEMETHODIMP GetState(_In_opt_ IShellItemArray*, _In_ BOOL, _Out_ EXPCMDSTATE* returned_state);
    IFACEMETHODIMP Invoke(_In_opt_ IShellItemArray*, _In_opt_ IBindCtx*) noexcept;
    IFACEMETHODIMP GetFlags(_Out_ EXPCMDFLAGS* returned_menu_item_flags);
    IFACEMETHODIMP EnumSubCommands(_COM_Outptr_ IEnumExplorerCommand** returned_enum_commands);
#pragma endregion

#pragma region IObjectWithSite
    IFACEMETHODIMP SetSite(_In_ IUnknown* site) noexcept;
    IFACEMETHODIMP GetSite(_In_ REFIID riid, _COM_Outptr_ void** site) noexcept;
#pragma endregion

protected:
    HINSTANCE instance_handle = 0;
    ComPtr<IUnknown> site_of_folder;
};
