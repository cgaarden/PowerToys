#pragma once

#include "pch.h"

using namespace Microsoft::WRL;

// The sub-context-menu that displays the list of templates
class rate_context_sub_menu_item : public RuntimeClass<RuntimeClassFlags<ClassicCom>, IExplorerCommand>
{
public:
    rate_context_sub_menu_item(const ComPtr<IUnknown> site_of_folder, std::wstring title, EXPCMDSTATE menu_item_state = ECS_ENABLED);

    // IExplorerCommand
    IFACEMETHODIMP GetTitle(_In_opt_ IShellItemArray* items, _Outptr_result_nullonfailure_ PWSTR* returned_title);

    IFACEMETHODIMP GetIcon(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_icon);

    IFACEMETHODIMP GetToolTip(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_info_tip);

    IFACEMETHODIMP GetCanonicalName(_Out_ GUID* guidCommandName);

    IFACEMETHODIMP GetState(_In_opt_ IShellItemArray* selection, _In_ BOOL, _Out_ EXPCMDSTATE* returned_state);

    IFACEMETHODIMP Invoke(_In_opt_ IShellItemArray* selection, _In_opt_ IBindCtx*) noexcept;

    IFACEMETHODIMP GetFlags(_Out_ EXPCMDFLAGS* returned_flags);

    IFACEMETHODIMP EnumSubCommands(_COM_Outptr_ IEnumExplorerCommand** enumCommands);

protected:
    rate_context_sub_menu_item();
    ComPtr<IUnknown> site_of_folder;
    std::wstring title;
    EXPCMDSTATE menu_item_state;
};
