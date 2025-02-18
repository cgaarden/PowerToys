#pragma once

#include "pch.h"

#include <common/Telemetry/TraceBase.h>

class Trace : public telemetry::TraceBase
{
public:
    static void EventToggleOnOff(_In_ const bool enabled_state) noexcept;

    // cgaarden more events
};
