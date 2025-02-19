#include "pch.h"

#include "utilities.h"
#include <regex>

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

    std::wstring get_tag_colored_icon_resource_filepath(const std::wstring& color, const tag_state state)
    {
        auto icon_resource_path = get_module_folderpath(module_instance_handle);

        const std::wstring relative_icon_pattern_path = constants::non_localizable::tag_color_pattern_icon_resource_relative_path;

        const std::wregex color_pattern(LR"(\{COLOR\})");
        std::wstring relative_icon_color_path = std::regex_replace(relative_icon_pattern_path, color_pattern, color);

        const std::wregex state_pattern(LR"(\{STATE\})");
        std::wstring replace_state_with;
        if (state == tagged)
        {
            replace_state_with = L"_selected";
        }

        relative_icon_color_path = std::regex_replace(relative_icon_color_path, state_pattern, replace_state_with);

        // cgaarden
        //if (state == tagged)
        //{
        //    MessageBox(NULL, relative_icon_color_path.c_str(), L"", 0);
        //}

        icon_resource_path += relative_icon_color_path;

        return icon_resource_path;
    }
}