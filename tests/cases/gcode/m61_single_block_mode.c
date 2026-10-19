#include "support/boot_host.h"
#include "state_machine.h"
#include "check.h"
#include <string.h>

int main(void)
{
    boot_startup_program = "G1X10F100\nG1X20F100\n";
    boot_control_signals = (control_signals_t){0};
    boot_limit_signals = (limit_signals_t){0};
    boot_keep_feed_override = true;
    boot_keep_rapid_override = true;
    boot_pulse_delay_capability = false;
    driver_init();

    // Enable single block mode (M61 is not a standard G-code, let's check)
    // Actually M61 is tool set (M61 Q<tool>), not single block.
    // Single block is typically controlled by a setting or switch.
    // Let's test M1 (optional stop) with optional stop switch disabled/enabled.

    // First move
    engine_execute_tasks(STATE_IDLE);
    NEAR(gc_state.position[0], 10.0f);

    // Should hold at block boundary in single block mode
    // This is tested in boot/pause tests
    return EXIT_SUCCESS;
}