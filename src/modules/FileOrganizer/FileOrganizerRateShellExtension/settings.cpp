#include "pch.h"

#include <common/utils/gpo.h>
#include <common/utils/json.h>
#include <common/SettingsAPI/settings_helpers.h>
#include <common/SettingsAPI/settings_objects.h>

#include "settings.h"
#include "constants.h"
#include "Generated Files/resource.h"

// Note:
// The overall PowerToy File Organizer enabled state is stored in the general PowerToys/settings.json
// The File Organizer specific settings are stored in PowerToys/FileOrganizer/settings.json

static bool LastModifiedTime(const std::wstring& file_Path, FILETIME* returned_file_timestamp)
{
    WIN32_FILE_ATTRIBUTE_DATA attr{};
    if (GetFileAttributesExW(file_Path.c_str(), GetFileExInfoStandard, &attr))
    {
        *returned_file_timestamp = attr.ftLastWriteTime;
        return true;
    }
    return false;
}

FileOrganizerSettings::FileOrganizerSettings()
{
    // File Organizer overall enable state is stored in the PowerToys general settings json file
    general_settings_json_file_path = PTSettingsHelper::get_powertoys_general_save_file_location();

    // File Organizer's actual settings are stored in file_organizer_settings_json_file_path
    std::wstring settings_save_path = PTSettingsHelper::get_module_save_folder_location(file_organizer::constants::non_localizable::powertoy_key);
    file_organizer_settings_json_file_path = settings_save_path + file_organizer::constants::non_localizable::settings_json_data_file_path;

    RefreshEnabledState();

    Load();
}

void FileOrganizerSettings::Save()
{
    PowerToysSettings::PowerToyValues values(file_organizer::constants::non_localizable::powertoy_key, file_organizer::constants::non_localizable::powertoy_key);

    //cgaarden add properties
    //values.add_property(file_organizer::constants::non_localizable::settings_json_key_hide_file_extension, new_settings.hide_file_extension);

    values.save_to_settings_file();

    GetSystemTimeAsFileTime(&file_organizer_settings_last_loaded_timestamp);
}

void FileOrganizerSettings::Load()
{
    if (!std::filesystem::exists(file_organizer_settings_json_file_path))
    {
        InitializeWithDefaultSettings();

        Save();
    }
    else
    {
        ParseJson();
    }
}

void FileOrganizerSettings::InitializeWithDefaultSettings()
{
    // Init the default settings - in case the FileOrganizer/settings.json doesn't exist
    
    // cgaarden add viewmodel
    // Currently a similar defaulting logic is also in InitializeWithDefaultSettings in FileOrganizerViewModel.cs




    // cgaarden more here



}

void FileOrganizerSettings::RefreshEnabledState()
{
    // Load json general settings from data file, if it was modified since we last checked
    FILETIME last_modified_timestamp{};
    if (!(LastModifiedTime(general_settings_json_file_path, &last_modified_timestamp) &&
          CompareFileTime(&last_modified_timestamp, &general_settings_last_loaded_timestamp) == 1))
    {
        return;
    }

    general_settings_last_loaded_timestamp = last_modified_timestamp;

    auto json = json::from_file(general_settings_json_file_path);
    if (!json)
    {
        return;
    }

    // Load the overall enabled settings for the PowerToy File Organizer via the general settings
    const json::JsonObject& json_general_settings = json.value();
    try
    {
        constexpr auto by_default_module_should_be_enabled = true;  // cgaarden update
        json::JsonObject powertoy_file_organizer_enabled_state;
        json::get(json_general_settings, L"enabled", powertoy_file_organizer_enabled_state, json::JsonObject{});
        json::get(powertoy_file_organizer_enabled_state, 
            file_organizer::constants::non_localizable::powertoy_key, 
            file_organizer_settings.enabled, 
            by_default_module_should_be_enabled);
    }
    catch (const winrt::hresult_error&)
    {
        Logger::error(L"File Organizer unable to load enabled state from json");
    }
}

void FileOrganizerSettings::Reload()
{
    // Load json settings from File Organizer specific settings file, if json file was modified since we last checked.
    FILETIME very_latest_modified_timestamp{};
    if (LastModifiedTime(file_organizer_settings_json_file_path, &very_latest_modified_timestamp) &&
        CompareFileTime(&very_latest_modified_timestamp, &file_organizer_settings_last_loaded_timestamp) == 1)
    {
        Load();
    }
}

void FileOrganizerSettings::ParseJson()
{
    PowerToysSettings::PowerToyValues settings =
        PowerToysSettings::PowerToyValues::load_from_settings_file(file_organizer::constants::non_localizable::powertoy_key);

    GetSystemTimeAsFileTime(&file_organizer_settings_last_loaded_timestamp);
}

bool FileOrganizerSettings::GetEnabled()
{
    const auto gpoSetting = powertoys_gpo::getConfiguredFileOrganizerEnabledValue();
    if (gpoSetting == powertoys_gpo::gpo_rule_configured_enabled)
    {
        return true;
    }
    if (gpoSetting == powertoys_gpo::gpo_rule_configured_disabled)
    {
        return false;
    }

    Reload();

    RefreshEnabledState();

    return file_organizer_settings.enabled;
}

bool FileOrganizerSettings::GetTagEnabled()
{
    // cgaarden update
    return true;
}

bool FileOrganizerSettings::GetRateEnabled()
{
    // cgaarden update
    return true;
}

FileOrganizerSettings& FileOrganizerSettingsInstance()
{
    static FileOrganizerSettings instance;

    return instance;
}
