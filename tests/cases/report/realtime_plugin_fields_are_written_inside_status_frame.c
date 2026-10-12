#include "support/report_host.h"
#include "check.h"
static unsigned extension_calls;
static void append_driver_field(stream_write_ptr write, report_tracking_flags_t flags) { (void)flags; CHECK(write == hal.stream.write); write("|Driver:ready"); extension_calls++; }
int main(void)
{
    prepare_report();
    grbl.on_realtime_report = append_driver_field;
    realtime_report();
    CHECK(strstr(engine_output, "|Driver:ready>" ASCII_EOL) != NULL);
    CHECK(extension_calls == 1);
    return EXIT_SUCCESS;
}
