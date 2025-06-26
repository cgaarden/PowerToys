#pragma once

#include "pch.h"
#include <string>
#include <vector>

//#include <common/utils/process_path.h>
//#include <common/utils/package.h>

namespace file_organizer::shared_utilities
{
    void RefreshShellForMultipleFiles(const std::vector<std::wstring>& file_paths);
    //void register_msix_package();

    //std::wstring get_tag_icon_resource_filepath(const HMODULE module_instance_handle, const Theme theme);

    //enum tag_state
    //{
    //    not_tagged,
    //    tagged
    //};
    //std::wstring get_tag_icon_number_resource_filepath(const std::wstring& number, const tag_state state = not_tagged);
}