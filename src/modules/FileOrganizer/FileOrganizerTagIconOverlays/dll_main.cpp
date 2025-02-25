#include "pch.h"

#include "dll_main.h"
#include "trace.h"
#include "shell_icon_overlays.h"

#include <common/Telemetry/EtwTrace/EtwTrace.h>

HMODULE module_instance_handle = 0;
Shared::Trace::ETWTrace trace(L"FileOrganizerTagShellExtension.Tag2");

BOOL APIENTRY DllMain(HMODULE module_handle, DWORD ul_reason_for_call, LPVOID reserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        module_instance_handle = module_handle;
        Trace::RegisterProvider();
        LoggerHelpers::init_logger(
            file_organizer::constants::non_localizable::powertoy_name,
            file_organizer::constants::non_localizable::module_name,
            LogSettings::fileOrganizerTagLoggerName);
        break;

    case DLL_PROCESS_DETACH:
        Trace::UnregisterProvider();
        break;
    }
    return TRUE;
}

STDAPI DllGetActivationFactory(_In_ HSTRING activatable_class_id, _COM_Outptr_ IActivationFactory** factory)
{
    return Module<ModuleType::InProc>::GetModule().GetActivationFactory(activatable_class_id, factory);
}

STDAPI DllCanUnloadNow()
{
    return Module<InProc>::GetModule().GetObjectCount() == 0 ? S_OK : S_FALSE;
}

STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID FAR* ppv)
{
    return Module<InProc>::GetModule().GetClassObject(rclsid, riid, ppv);
}

CoCreatableClass(tag_icon_overlay_handler_1)
CoCreatableClass(tag_icon_overlay_handler_2)
CoCreatableClass(tag_icon_overlay_handler_3)
CoCreatableClass(tag_icon_overlay_handler_4)
CoCreatableClass(tag_icon_overlay_handler_5)
CoCreatableClass(tag_icon_overlay_handler_6)
CoCreatableClass(tag_icon_overlay_handler_7)
CoCreatableClass(tag_icon_overlay_handler_8)
CoCreatableClass(tag_icon_overlay_handler_9)
CoCreatableClass(tag_icon_overlay_handler_multiple)
