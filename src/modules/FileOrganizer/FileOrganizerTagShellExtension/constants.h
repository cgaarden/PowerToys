#pragma once

#include "pch.h"

namespace file_organizer::constants::non_localizable
{
    constexpr WCHAR powertoy_key[] = L"FileOrganizer";

    constexpr WCHAR powertoy_name[] = L"FileOrganizer";

    constexpr WCHAR settings_json_data_file_path[] = LR"(\settings.json)";

    constexpr WCHAR context_menu_package_name[] = L"FileOrganizer.Tag.ContextMenu";

    constexpr WCHAR msix_package_name[] = L"FileOrganizer.Tag.Package.msix";
    
    constexpr WCHAR module_name[] = L"FileOrganizer.Tag.ShellExtension";

    constexpr WCHAR tag_menu_icon_light_resource_relative_path[] = LR"(\Assets\FileOrganizer.Tag\tag_light.ico)";
}
