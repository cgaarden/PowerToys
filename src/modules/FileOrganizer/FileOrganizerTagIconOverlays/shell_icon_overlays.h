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

class __declspec(uuid("6E3F4F51-9C60-4204-8E3D-D424AF7DC0AB")) tag_icon_overlay_handler_4 final :
    public shell_icon_overlay_base
{
public:
    tag_icon_overlay_handler_4();
};

class __declspec(uuid("6E3F4F51-9C60-4205-8E3D-D424AF7DC0AB")) tag_icon_overlay_handler_5 final :
    public shell_icon_overlay_base
{
public:
    tag_icon_overlay_handler_5();
};

class __declspec(uuid("6E3F4F51-9C60-4206-8E3D-D424AF7DC0AB")) tag_icon_overlay_handler_6 final :
    public shell_icon_overlay_base
{
public:
    tag_icon_overlay_handler_6();
};

class __declspec(uuid("6E3F4F51-9C60-4207-8E3D-D424AF7DC0AB")) tag_icon_overlay_handler_7 final :
    public shell_icon_overlay_base
{
public:
    tag_icon_overlay_handler_7();
};

class __declspec(uuid("6E3F4F51-9C60-4208-8E3D-D424AF7DC0AB")) tag_icon_overlay_handler_8 final :
    public shell_icon_overlay_base
{
public:
    tag_icon_overlay_handler_8();
};

class __declspec(uuid("6E3F4F51-9C60-4209-8E3D-D424AF7DC0AB")) tag_icon_overlay_handler_9 final :
    public shell_icon_overlay_base
{
public:
    tag_icon_overlay_handler_9();
};

class __declspec(uuid("6E3F4F51-9C60-420a-8E3D-D424AF7DC0AB")) tag_icon_overlay_handler_multiple final :
    public shell_icon_overlay_base
{
public:
    tag_icon_overlay_handler_multiple();
};
