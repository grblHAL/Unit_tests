#include "support/report_host.h"
#include "stream.h"
#include "check.h"

int main(void)
{
    prepare_report();
    hal.stream.state.is_usb = true;
    stream_usb_linestate_changed(0, (serial_linestate_t){.dtr = true});
    engine_ticks = 199;
    engine_execute_tasks(STATE_IDLE);
    CHECK(engine_output[0] == '\0');
    engine_ticks = 200;
    engine_execute_tasks(STATE_IDLE);
    CHECK(strstr(engine_output, "GrblHAL " GRBL_VERSION) != NULL);
    return EXIT_SUCCESS;
}
