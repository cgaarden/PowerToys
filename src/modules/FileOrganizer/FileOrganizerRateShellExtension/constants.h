#pragma once

#include "pch.h"

namespace file_organizer::constants::non_localizable
{
    constexpr WCHAR powertoy_key[] = L"FileOrganizer";

    constexpr WCHAR powertoy_name[] = L"FileOrganizer";

    constexpr WCHAR settings_json_data_file_path[] = LR"(\settings.json)";

    constexpr WCHAR context_menu_package_name[] = L"FileOrganizer.Rate.ContextMenu";

    constexpr WCHAR msix_package_name[] = L"FileOrganizer.Rate.Package.msix";
    
    constexpr WCHAR module_name[] = L"FileOrganizer.Rate.ShellExtension";

    constexpr WCHAR rate_menu_icon_light_resource_relative_path[] = LR"(\Assets\FileOrganizer.Rate\rate_light.ico)";
}
