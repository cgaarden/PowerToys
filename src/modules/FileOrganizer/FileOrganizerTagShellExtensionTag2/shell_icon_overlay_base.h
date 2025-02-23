#pragma once

#include "pch.h"

using namespace Microsoft::WRL;

class shell_icon_overlay_base :
    public RuntimeClass<
        RuntimeClassFlags<ClassicCom>,
        IShellIconOverlayIdentifier>
{
public:
#pragma region IShellIconOverlayIdentifier
    IFACEMETHODIMP GetOverlayInfo(LPWSTR returned_icon_file, int max_icon_file_buffer, int* returned_icon_index, DWORD* returned_icon_flags);
    IFACEMETHODIMP GetPriority(int* returned_priority);
    IFACEMETHODIMP IsMemberOf(LPCWSTR full_path, DWORD file_attributes);
#pragma endregion

protected:
    int handler_priority = 0;
    std::wstring file_name;
    std::wstring icon_resource_filepath;
};

class __declspec(uuid("6E3F4F51-9C60-4201-8E3D-D424AF7DC0AB")) tag_icon_overlay_handler_1 final :
    public shell_icon_overlay_base
{
public:
    tag_icon_overlay_handler_1();
};

class __declspec(uuid("6E3F4F51-9C60-4202-8E3D-D424AF7DC0AB")) tag_icon_overlay_handler_2 final : 
    public shell_icon_overlay_base
{
public:
    tag_icon_overlay_handler_2();
};

class __declspec(uuid("6E3F4F51-9C60-4203-8E3D-D424AF7DC0AB")) tag_icon_overlay_handler_3 final :
    public shell_icon_overlay_base
{
public:
    tag_icon_overlay_handler_3();
};
