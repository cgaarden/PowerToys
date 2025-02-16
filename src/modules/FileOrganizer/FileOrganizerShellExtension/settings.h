#pragma once

#include "pch.h"

class FileOrganizerSettings
{
public:
    FileOrganizerSettings();

    bool GetEnabled();

    void Save();
    void Load();

private:
    struct Settings
    {
        bool enabled{ false };
    };

    void RefreshEnabledState();
    void InitializeWithDefaultSettings();

    void Reload();
    void ParseJson();

    Settings file_organizer_settings;
    std::wstring general_settings_json_file_path;
    std::wstring file_organizer_settings_json_file_path;
    FILETIME general_settings_last_loaded_timestamp{};
    FILETIME file_organizer_settings_last_loaded_timestamp{};
};

FileOrganizerSettings& FileOrganizerSettingsInstance();
