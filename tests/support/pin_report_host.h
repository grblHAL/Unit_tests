#pragma once
#include "support/report_host.h"
static unsigned pin_enumerations;
static xbar_t report_pins_data[] = {
    {.pin = 3, .function = Output_StepZ, .port = "PB", .description = "z motor"},
    {.pin = 1, .function = Output_StepX, .port = "PA", .description = "x motor"},
    {.pin = 2, .function = Output_StepY}
};
static void enumerate_report_pins(bool low_level, pin_info_ptr callback, void *data)
{
    CHECK(!low_level);
    pin_enumerations++;
    for(unsigned i = 0; i < sizeof(report_pins_data) / sizeof(report_pins_data[0]); i++)
        callback(&report_pins_data[i], data);
}
static inline void prepare_pin_report(void)
{
    prepare_report();
    hal.enumerate_pins = enumerate_report_pins;
}
