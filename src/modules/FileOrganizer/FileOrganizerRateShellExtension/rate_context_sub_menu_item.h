#pragma once

#include "pch.h"

using namespace Microsoft::WRL;

class rate_context_sub_menu_item : public RuntimeClass<RuntimeClassFlags<ClassicCom>, IExplorerCommand>
{
public:
    rate_context_sub_menu_item(const ComPtr<IUnknown> site_of_folder, unsigned int rate, std::wstring title, EXPCMDSTATE menu_item_state = ECS_ENABLED);

    // IExplorerCommand
    IFACEMETHODIMP GetTitle(_In_opt_ IShellItemArray* selection, _Outptr_result_nullonfailure_ PWSTR* returned_title);

    IFACEMETHODIMP GetIcon(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_icon);

    IFACEMETHODIMP GetToolTip(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_info_tip);

    IFACEMETHODIMP GetCanonicalName(_Out_ GUID* guidCommandName);

    IFACEMETHODIMP GetState(_In_opt_ IShellItemArray* selection, _In_ BOOL, _Out_ EXPCMDSTATE* returned_state);

    IFACEMETHODIMP Invoke(_In_opt_ IShellItemArray* selection, _In_opt_ IBindCtx*) noexcept;

    IFACEMETHODIMP GetFlags(_Out_ EXPCMDFLAGS* returned_flags);

    IFACEMETHODIMP EnumSubCommands(_COM_Outptr_ IEnumExplorerCommand** enumCommands);

protected:
    ComPtr<IUnknown> site_of_object;
    unsigned int rate;
    std::wstring title;
    EXPCMDSTATE menu_item_state;
};

// Sub-context-menu separator
class rate_separator_context_menu_item final : public rate_context_sub_menu_item
{
public:
    rate_separator_context_menu_item() :
        rate_context_sub_menu_item(nullptr, 0, L"", ECS_DISABLED) 
    {
    }

    IFACEMETHODIMP GetTitle(_In_opt_ IShellItemArray* items, _Outptr_result_nullonfailure_ PWSTR* returned_title);

    IFACEMETHODIMP GetIcon(_In_opt_ IShellItemArray*, _Outptr_result_nullonfailure_ PWSTR* returned_icon);

    IFACEMETHODIMP GetState(_In_opt_ IShellItemArray* selection, _In_ BOOL, _Out_ EXPCMDSTATE* returned_state);

    IFACEMETHODIMP GetFlags(_Out_ EXPCMDFLAGS* returned_flags);
};