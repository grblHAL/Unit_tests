#include "support/boot_host.h"
#include "state_machine.h"
#include "check.h"
#include <string.h>

int main(void)
{
    boot_startup_program = "G1X10F100\nM60\nG1X20F100\n";
    boot_control_signals = (control_signals_t){0};
    boot_limit_signals = (limit_signals_t){0};
    boot_keep_feed_override = true;
    boot_keep_rapid_override = true;
    boot_pulse_delay_capability = false;
    driver_init();

    // First move should execute
    engine_execute_tasks(STATE_IDLE);
    // Position should be at X=10
    NEAR(gc_state.position[0], 10.0f);

    // M60 should cause a hold
    CHECK(state_get() == STATE_HOLD);

    // Position should be preserved
    NEAR(gc_state.position[0], 10.0f);

    // Cycle start (simulate by clearing hold)
    sys.flags.hold = false;
    engine_execute_tasks(STATE_CYCLE);

    // Second move should execute
    // Position should be at X=20
    NEAR(gc_state.position[0], 20.0f);

    return EXIT_SUCCESS;
}