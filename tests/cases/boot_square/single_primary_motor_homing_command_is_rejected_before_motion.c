#include "support/boot_host.h"
static void configure_homing_commands(settings_t *current)
{
    CHECK(current == &settings);
    current->homing.flags.single_axis_commands = true;
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        current->axis[axis].homing_seek_rate = 100;
        current->axis[axis].homing_feed_rate = 25;
    }
}
int main(void)
{
    boot_homing_required = true;
    boot_during_setup = configure_homing_commands;
    boot_program = "$HY\n";
    CHECK(grbl_enter() == 0);
    CHECK(sys.homed.mask == 0);
    CHECK(plan_get_current_block() == NULL);
    CHECK(strstr(engine_output, "ALARM:18") != NULL);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    return EXIT_SUCCESS;
}
