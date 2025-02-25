#pragma once

#include "pch.h"

using namespace Microsoft::WRL;

#define FILE_ORGANIZER_SHELL_EXTENSION_TAG_EXPLORER_COMMAND_UUID_STR "6E3F4F51-9C60-42B8-8E3D-D424AF7DC0AB"

class __declspec(uuid(FILE_ORGANIZER_SHELL_EXTENSION_TAG_EXPLORER_COMMAND_UUID_STR)) tag_shell_extensions_icon_overlay_tag2 final :
    public RuntimeClass<
        RuntimeClassFlags<ClassicCom>,
        IShellIconOverlayIdentifier>
{
public:
#pragma region IShellIconOverlayIdentifier
    IFACEMETHODIMP GetOverlayInfo(LPWSTR pwszIconFile, int cchMax, int* pIndex, DWORD* pdwFlags);
    IFACEMETHODIMP GetPriority(int* pPriority);
    IFACEMETHODIMP IsMemberOf(LPCWSTR pwszPath, DWORD dwAttrib);
#pragma endregion

protected:
    HINSTANCE instance_handle = 0;
};
