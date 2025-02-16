#pragma once

#include "pch.h"
#include <common/utils/process_path.h>
#include <common/utils/package.h>

namespace file_organizer::utilities
{
    inline void register_msix_package()
    {
        if (package::IsWin11OrGreater())
        {
            static const auto dll_path = get_module_folderpath(module_instance_handle);
            static const auto package_uri = dll_path + L"\\" + constants::non_localizable::msix_package_name;

            if (!package::IsPackageRegistered(constants::non_localizable::context_menu_package_name))
            {
                package::RegisterSparsePackage(dll_path, package_uri);
            }
        }
    }
}