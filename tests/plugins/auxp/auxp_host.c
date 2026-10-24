#include "auxp_host.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
char output[256];
unsigned writes, resets, reports, options;
uint8_t last_port;
bool last_value;
static void write_text(const char *s)
{
    CHECK(strlen(output) + strlen(s) < sizeof(output));
    strcat(output, s);
}
static void digital(uint8_t port, bool on)
{
    writes++;
    last_port = port;
    last_value = on;
}
static void reset(void) { resets++; }
static void report(stream_write_ptr write, report_tracking_flags_t flags)
{
    (void)flags;
    reports++;
    write("|previous");
}
static void option(bool newopt)
{
    (void)newopt;
    options++;
}
bool protocol_execute_realtime(void)
{
    CHECK(false);
    return false;
}
bool protocol_exec_rt_system(void)
{
    CHECK(false);
    return false;
}
bool state_door_reopened(void)
{
    CHECK(false);
    return false;
}
void auxp_prepare(bool chained)
{
    hal.stream.write = write_text;
    if (chained)
    {
        hal.port.digital_out = digital;
        hal.driver_reset = reset;
        grbl.on_realtime_report = report;
        grbl.on_report_options = option;
    }
    auxp_init();
}
void auxp_report(bool all)
{
    output[0] = 0;
    report_tracking_flags_t flags = {0};
    flags.all = all;
    grbl.on_realtime_report(write_text, flags);
}
