#pragma once

#include "pch.h"
#include <common/utils/process_path.h>
#include <common/utils/package.h>

namespace file_organizer::utilities
{
    void register_msix_package();

    std::wstring get_tag_icon_resource_filepath(const HMODULE module_instance_handle, const Theme theme);

    enum tag_state
    {
        not_tagged,
        tagged
    };
    std::wstring get_tag_colored_icon_resource_filepath(const std::wstring& color, const tag_state state = not_tagged);
}