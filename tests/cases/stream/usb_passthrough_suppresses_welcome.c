#include "support/report_host.h"
#include "stream.h"
#include "check.h"

int main(void)
{
    prepare_report();
    hal.stream.state.is_usb = true;
    hal.stream.state.passthru = true;
    stream_usb_linestate_changed(0, (serial_linestate_t){.dtr = true});
    engine_ticks = 200;
    engine_execute_tasks(STATE_IDLE);
    CHECK(engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
