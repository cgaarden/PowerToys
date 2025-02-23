#include "pch.h"

#include "tag_shell_extensions_icon_overlay_tag2.h"
#include "utilities.h"
#include <common/logger/logger.h>

// Note: You likely need to restart explorer.exe when making changes for IconOverlays

// "The Shell calls IShellIconOverlayIdentifier::GetOverlayInfo to request the
//  location of the handler's icon overlay. The icon overlay handler returns
//  the name of the file containing the overlay image, and its index within
//  that file. The Shell then adds the icon overlay to the system image list."

STDMETHODIMP tag_shell_extensions_icon_overlay_tag2::GetOverlayInfo(LPWSTR pwszIconFile, int cchMax, int* pIndex, DWORD* pdwFlags)
{
    if (!pwszIconFile)
        return E_POINTER;
    if (!pIndex)
        return E_POINTER;
    if (!pdwFlags)
        return E_POINTER;
    if (cchMax < 1)
        return E_INVALIDARG;

    // Set "out parameters" since we return S_OK later.
    *pwszIconFile = 0;
    *pIndex = 0;
    *pdwFlags = 0;

    static const auto icon_resource_filepath = file_organizer::utilities::get_tag_icon_number_resource_filepath(L"2");
    wcscpy_s(pwszIconFile, cchMax, icon_resource_filepath.c_str());
    *pIndex = 0;
    *pdwFlags = ISIOI_ICONFILE;
    return S_OK;

    return S_OK;
};

STDMETHODIMP tag_shell_extensions_icon_overlay_tag2::GetPriority(int* pPriority)
{
    if (!pPriority)
        return E_POINTER;
    
    *pPriority = 1;

    return S_OK;
}

// "Before painting an object's icon, the Shell passes the object's name to
//  each icon overlay handler's IShellIconOverlayIdentifier::IsMemberOf
//  method. If a handler wants to have its icon overlay displayed,
//  it returns S_OK. The Shell then calls the handler's
//  IShellIconOverlayIdentifier::GetOverlayInfo method to determine which icon
//  to display."

STDMETHODIMP tag_shell_extensions_icon_overlay_tag2::IsMemberOf(LPCWSTR pwszPath, DWORD /*dwAttrib*/)
{
    if (!pwszPath)
        return E_INVALIDARG;

    const wchar_t* pPath = pwszPath;

    // the shell sometimes asks overlays for invalid paths, e.g. for network
    // printers (in that case the path is "0", at least for me here).
    if (wcslen(pPath) < 2)
        return S_FALSE;

    if (wcsstr(pwszPath, L"2.txt") != nullptr)
    {
        return S_OK;
    }

    return S_FALSE;

}
