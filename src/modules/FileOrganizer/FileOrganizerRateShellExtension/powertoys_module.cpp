#include "pch.h"

#include <filesystem>
#include <string>

#include <winrt/Windows.Data.Json.h>

#include <common/SettingsAPI/settings_objects.h>
#include <common/utils/gpo.h>
#include <common/utils/process_path.h>
#include <common/utils/resources.h>
#include <interface/powertoy_module_interface.h>

#include "settings.h"
#include "trace.h"
#include "Generated Files/resource.h"

// Note: Settings are managed via Settings and UI Settings
class FileOrganizerPowerToysModule : public PowertoyModuleIface
{
public:
    FileOrganizerPowerToysModule()
    {
        init_settings();
    }

    virtual const wchar_t* get_name() override
    {
        static const std::wstring localized_product_name =
            GET_RESOURCE_STRING_FALLBACK(IDS_PRODUCT_NAME, L"File Organizer - Rate");

        return localized_product_name.c_str();
    }

    virtual const wchar_t* get_key() override
    {
        // This setting key must match EnabledModules.cs [JsonPropertyName("FileOrganizer")]
        return file_organizer::constants::non_localizable::powertoy_key;
    }

    virtual powertoys_gpo::gpo_rule_configured_t gpo_policy_enabled_configuration() override
    {
        return powertoys_gpo::getConfiguredFileOrganizerEnabledValue();
    }

    virtual bool get_config(_Out_ PWSTR buffer, _Out_ int* buffer_size) override
    {
        // Not implemented as Settings are propagating via json
        return true;
    }

    virtual void set_config(const wchar_t* config) override
    {
        // The following just checks to see if the Template Location was changed for metrics purposes
        // Note: We are not saving the settings here and instead relying on read/write of json in Settings App .cs code paths
        try
        {
            // Parse the input JSON string.
            PowerToysSettings::PowerToyValues values =
                PowerToysSettings::PowerToyValues::from_json_string(config, get_key());

            values.save_to_settings_file();
            FileOrganizerSettingsInstance().Load();

            // cgaarden add code
            //auto templateValue = values.get_string_value(file_organizer::constants::non_localizable::settings_json_key_template_location);
            //if (templateValue.has_value())
            //{
            //    const auto latest_location_value = templateValue.value();
            //    const auto existing_location_value = NewSettingsInstance().GetTemplateLocation();
            //    if (!newplus::utilities::wstring_same_when_comparing_ignore_case(latest_location_value, existing_location_value))
            //    {
            //        Trace::EventChangedTemplateLocation();
            //    }
            //}

        }
        catch (std::exception& e)
        {
            Logger::error("Configuration parsing failed: {}", std::string{ e.what() });
        }
    }

    virtual bool is_enabled_by_default() const override
    { 
        return false; 
    }

    virtual void enable() override
    {
        Logger::info("File Organizer enabled via Settings UI");

        // Log telemetry
        Trace::EventToggleOnOff(true);

        file_organizer::utilities::register_msix_package();

        powertoy_file_organizer_enabled = true;
    }

    virtual void disable() override
    {
        Logger::info("File Organizer disabled via Settings UI");
        Disable(true);
    }

    virtual bool is_enabled() override
    {
        return powertoy_file_organizer_enabled;
    }
        
    virtual void destroy() override
    {
        Disable(false);
        delete this;
    }

private:
    bool powertoy_file_organizer_enabled = false;

    void Disable(bool const traceEvent)
    {
        // Log telemetry
        if (traceEvent)
        {
            Trace::EventToggleOnOff(false);
        }
        powertoy_file_organizer_enabled = false;
    }

    void init_settings()
    {
        powertoy_file_organizer_enabled = FileOrganizerSettingsInstance().GetEnabled();
    }
};

extern "C" __declspec(dllexport) PowertoyModuleIface* __cdecl powertoy_create()
{
    return new FileOrganizerPowerToysModule();
}
