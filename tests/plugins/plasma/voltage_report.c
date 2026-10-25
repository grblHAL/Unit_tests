#include "plasma_host.h"
int main(void)
{
    plasma_boot();
    plasma_set(Setting_Arc_VoltageOffset, 10);
    plasma_set(Setting_Arc_VoltageScale, 2);
    plasma_voltage = 70;
    plasma_tick(5);
    plasma_output[0] = 0;
    grbl.on_report_options(false);
    CHECK(strstr(plasma_output, "PLASMA (Voltage)"));
    grbl.on_realtime_report(hal.stream.write, (report_tracking_flags_t){0});
    CHECK(strstr(plasma_output, "|THC:120.0") && strstr(plasma_output, "|Previous:1"));
    return 0;
}
