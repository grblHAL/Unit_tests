#pragma once
#include "support/mpg_stream_host.h"
#include "support/settings_host.h"
static bool reject_pendant_baud(uint32_t baud)
{
    (void)baud; pendant_baud_calls++; return false;
}
static inline void prepare_mpg_settings(bool reject_baud)
{
    prepare_mpg_stream();
    hal.driver_cap.mpg_mode = true;
    grbl.on_settings_changed = changed_settings;
    io_stream_t device = pendant_device;
    if(reject_baud) device.set_baud_rate = reject_pendant_baud;
    CHECK(stream_mpg_register(&device, true, NULL));
}
