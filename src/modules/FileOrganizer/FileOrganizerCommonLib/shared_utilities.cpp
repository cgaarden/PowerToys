#include "pch.h"

#include "shared_utilities.h"
#include <ShlObj_core.h>

namespace file_organizer::shared_utilities
{
    void RefreshShellForMultipleFiles(const std::vector<std::wstring>& file_paths)
    {
        for (const auto& file_path : file_paths)
        {
            SHChangeNotify(SHCNE_UPDATEITEM, SHCNF_PATH | SHCNF_FLUSH, file_path.c_str(), NULL);
        }
    }

    // cgaarden
    //void register_msix_package()
    //{
    //    if (package::IsWin11OrGreater())
    //    {
    //        static const auto dll_path = get_module_folderpath(module_instance_handle);
    //        static const auto package_uri = dll_path + L"\\" + constants::non_localizable::msix_package_name;

    //        if (!package::IsPackageRegisteredWithPowerToysVersion(constants::non_localizable::context_menu_package_name))
    //        {
    //            package::RegisterSparsePackage(dll_path, package_uri);
    //        }
    //    }
    //}

    // cgaarden
    //std::wstring get_tag_icon_resource_filepath(const HMODULE module_instance_handle, const Theme theme)
    //{
    //    auto icon_resource_path = get_module_folderpath(module_instance_handle);

    //    icon_resource_path += constants::non_localizable::tag_menu_icon_light_resource_relative_path;

    //    return icon_resource_path;
    //}

}