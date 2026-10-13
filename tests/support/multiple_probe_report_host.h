#pragma once
#include "support/realtime_pins_host.h"
#include "support/multiple_probe_host.h"
static void prepare_multiple_probe_report(void)
{
    prepare_realtime_pins();
    register_multiple_probes();
    CHECK(hal.probe.select(Probe_2));
}
