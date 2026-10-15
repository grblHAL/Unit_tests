#include "support/passthru_host.h"
#include "state_machine.h"
static unsigned driver_entries;
void stream_passthru_enter(void) { driver_entries++; }
int main(void)
{
    prepare_passthru();
    stream_passthru_init(1, 115200, false);
    state_set(STATE_IDLE);
    char command[] = "$PTRGH=1";
    CHECK(system_execute_line(command, hal.stream.write) == Status_InvalidStatement);
    CHECK(driver_entries == 0 && !hal.stream.state.passthru);
    CHECK(engine_ticks == 0);
    return EXIT_SUCCESS;
}
