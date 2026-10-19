#pragma once
#include "support/boot_host.h"
static bool boot_protection_enabled = true;
static void install_probe_protection(void)
{
    hal.signals_cap.probe_triggered = true;
    settings.probe.enable_protection = boot_protection_enabled;
    settings_write_global();
}
