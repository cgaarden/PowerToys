#pragma once

#include "pch.h"
#include "rate_context_sub_menu_collection.h"

using namespace Microsoft::WRL;

// // Sub context menu command enumerator
class rate_context_sub_menu_collection final : public RuntimeClass<RuntimeClassFlags<ClassicCom>, IEnumExplorerCommand>
{
public:
    rate_context_sub_menu_collection(const ComPtr<IUnknown> site_of_folder);

    // IEnumExplorerCommand
    IFACEMETHODIMP Next(ULONG celt, __out_ecount_part(celt, *pceltFetched) IExplorerCommand** apUICommand, __out_opt ULONG* pceltFetched);
    IFACEMETHODIMP Skip(ULONG);
    IFACEMETHODIMP Reset();
    IFACEMETHODIMP Clone(__deref_out IEnumExplorerCommand** returned_enum_not_used);

protected:
    std::vector<ComPtr<IExplorerCommand>> explorer_menu_item_commands;
    std::vector<ComPtr<IExplorerCommand>>::const_iterator current_command;
    ComPtr<IUnknown> site_of_folder;
};
