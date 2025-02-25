#include "pch.h"

#include "shell_icon_overlays.h"
#include "utilities.h"
#include <common/logger/logger.h>

// Note: 
// You likely will need to restart explorer.exe when making changes to icon overlays
// and sometimes, you'll EVEN need to logout or restart your computer

IFACEMETHODIMP shell_icon_overlay_base::GetOverlayInfo(LPWSTR returned_icon_file, int max_icon_file_buffer, int* returned_icon_index, DWORD* returned_icon_flags)
{
    *returned_icon_file = 0;
    *returned_icon_index = 0;

    // cgaarden
    wcscpy_s(returned_icon_file, max_icon_file_buffer, icon_resource_filepath.c_str());
    *returned_icon_flags = ISIOI_ICONFILE;

    std::wstring temp_message = L"shell_icon_overlay_base: ";
    temp_message += returned_icon_file;
    Logger::info(temp_message.c_str());

    return S_OK;
};

IFACEMETHODIMP shell_icon_overlay_base::GetPriority(int* returned_priority)
{
    *returned_priority = handler_priority;

    return S_OK;
}

IFACEMETHODIMP shell_icon_overlay_base::IsMemberOf(LPCWSTR full_path, DWORD file_attributes)
{
    if (!full_path)
    {
        return E_INVALIDARG;
    }

    if (wcslen(full_path) < 4)
    {
        return S_FALSE;
    }

    // cgaarden
    //std::wstring temp_message = L"shell_icon_overlay_base: ";
    //temp_message += full_path;
    //Logger::error(temp_message.c_str());

    if (wcsstr(full_path, file_name.c_str()) != nullptr)
    {
        // cgaarden
        if (file_name == L"s.txt")
        {
            Logger::info(file_name.c_str());
        }
        return S_OK;
    }

    return S_FALSE;
}

tag_icon_overlay_handler_1::tag_icon_overlay_handler_1()
{
    handler_priority = 1;
    file_name = L"1.txt";
    icon_resource_filepath = file_organizer::utilities::get_tag_icon_number_resource_filepath(L"1");
};

tag_icon_overlay_handler_2::tag_icon_overlay_handler_2()
{
    handler_priority = 2;
    file_name = L"2.txt";
    icon_resource_filepath = file_organizer::utilities::get_tag_icon_number_resource_filepath(L"2");
};

tag_icon_overlay_handler_3::tag_icon_overlay_handler_3()
{
    handler_priority = 3;
    file_name = L"3.txt";
    icon_resource_filepath = file_organizer::utilities::get_tag_icon_number_resource_filepath(L"3");
};

tag_icon_overlay_handler_4::tag_icon_overlay_handler_4()
{
    handler_priority = 4;
    file_name = L"4.txt";
    icon_resource_filepath = file_organizer::utilities::get_tag_icon_number_resource_filepath(L"4");
};

tag_icon_overlay_handler_5::tag_icon_overlay_handler_5()
{
    handler_priority = 5;
    file_name = L"5.txt";
    icon_resource_filepath = file_organizer::utilities::get_tag_icon_number_resource_filepath(L"5");
};

tag_icon_overlay_handler_6::tag_icon_overlay_handler_6()
{
    handler_priority = 6;
    file_name = L"6.txt";
    icon_resource_filepath = file_organizer::utilities::get_tag_icon_number_resource_filepath(L"6");
};

tag_icon_overlay_handler_7::tag_icon_overlay_handler_7()
{
    handler_priority = 7;
    file_name = L"7.txt";
    icon_resource_filepath = file_organizer::utilities::get_tag_icon_number_resource_filepath(L"7");
};

tag_icon_overlay_handler_8::tag_icon_overlay_handler_8()
{
    handler_priority = 8;
    file_name = L"8.txt";
    icon_resource_filepath = file_organizer::utilities::get_tag_icon_number_resource_filepath(L"8");
};

tag_icon_overlay_handler_9::tag_icon_overlay_handler_9()
{
    handler_priority = 9;
    file_name = L"9.txt";
    icon_resource_filepath = file_organizer::utilities::get_tag_icon_number_resource_filepath(L"9");
};

tag_icon_overlay_handler_multiple::tag_icon_overlay_handler_multiple()
{
    handler_priority = 10;
    file_name = L"tags.txt";
    icon_resource_filepath = file_organizer::utilities::get_tag_icon_number_resource_filepath(L"multiple");
};
