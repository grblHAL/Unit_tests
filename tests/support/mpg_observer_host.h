#pragma once
#include "support/mpg_stream_host.h"
static unsigned previous_calls, description_calls;
static report_tracking_flags_t previous_flags;
static inline void previous_reports(report_tracking_flags_t flags) { previous_calls++; previous_flags = flags; }
static inline void previous_modes(void) { previous_calls++; }
static inline void describe_rx(pin_function_t function, pin_group_t group, const char *description)
{
    CHECK(function == Input_RX && group == PinGroup_UART + 1);
    CHECK(strcmp(description,"MPG") == 0); description_calls++;
}
