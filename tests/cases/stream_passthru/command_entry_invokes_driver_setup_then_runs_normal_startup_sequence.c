#include "support/passthru_host.h"
#include "state_machine.h"
static unsigned driver_entries;
static bool usb_connected(void) { return true; }
void stream_passthru_enter(void)
{
    driver_entries++;
    stream_passthru_init(1, 115200, true);
}
int main(void)
{
    prepare_passthru();
    hal.stream.is_connected = usb_connected;
    report_init_fns(); report_init();
    stream_passthru_init(1, 115200, false);
    CHECK(!hal.stream.state.passthru);
    state_set(STATE_IDLE);
    char command[] = "$PTRGH";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(driver_entries == 1 && hal.stream.state.passthru);
    CHECK(engine_ticks == 100);
    CHECK(strstr(engine_output, "Entering passthru mode") != NULL);
    sys.driver_started = true;
    task_execute_on_startup();
    CHECK(pin_values[0] && !pin_values[1]);
    engine_ticks += 1250;
    engine_execute_tasks(STATE_IDLE);
    CHECK(pin_values[1] && cancelled == 1);
    return EXIT_SUCCESS;
}
