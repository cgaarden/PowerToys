#pragma once

#include "pch.h"
#include <common/utils/process_path.h>
#include <common/utils/package.h>

namespace file_organizer::utilities
{
    void register_msix_package();
    std::wstring get_rate_icon_resource_filepath(const HMODULE module_instance_handle, const Theme theme);
    std::wstring get_tag_icon_resource_filepath(const HMODULE module_instance_handle, const Theme theme);
}