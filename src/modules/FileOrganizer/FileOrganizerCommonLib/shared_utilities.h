#pragma once

#include "pch.h"
#include <atlbase.h>
#include <string>
#include <Shobjidl.h>
#include <vector>

namespace file_organizer::shared_utilities
{
    // Extracts file paths from an IShellItemArray
    std::vector<std::wstring> GetFilePathsFromShellItemArray(IShellItemArray* selection);
    void RefreshShellForMultipleFiles(const std::vector<std::wstring>& file_paths);
}

    //void register_msix_package();

    //std::wstring get_tag_icon_resource_filepath(const HMODULE module_instance_handle, const Theme theme);

    //enum tag_state
    //{
    //    not_tagged,
    //    tagged
    //};
    //std::wstring get_tag_icon_number_resource_filepath(const std::wstring& number, const tag_state state = not_tagged);
