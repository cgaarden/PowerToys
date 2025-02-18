#include "pch.h"

#include "utilities.h"

namespace file_organizer::utilities
{
    void register_msix_package()
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

    std::wstring get_tag_icon_resource_filepath(const HMODULE module_instance_handle, const Theme theme)
    {
        auto icon_resource_path = get_module_folderpath(module_instance_handle);

        icon_resource_path += constants::non_localizable::tag_menu_icon_light_resource_relative_path;

        return icon_resource_path;
    }
}