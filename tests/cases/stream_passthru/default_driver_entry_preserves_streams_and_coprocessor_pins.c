#include "support/passthru_host.h"
#include "state_machine.h"

static bool usb_connected(void) { return true; }

int main(void)
{
    prepare_passthru();
    hal.stream.is_connected = usb_connected;
    report_init_fns();
    report_init();
    stream_passthru_init(1, 115200, false);
    state_set(STATE_IDLE);
    char command[] = "$PTRGH";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(engine_ticks == 100 && !hal.stream.state.passthru);
    CHECK(usb_handler == NULL && uart_handler == NULL);
    CHECK(!pin_values[0] && !pin_values[1] && cancelled == 0);
    CHECK(hal.stream.on_linestate_changed == NULL);
    CHECK(strstr(engine_output, "Entering passthru mode") != NULL);
    return EXIT_SUCCESS;
}
