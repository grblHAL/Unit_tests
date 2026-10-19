#include "support/laser_program_host.h"
#include "support/settings_host.h"
static void coolant_off(coolant_state_t state) { CHECK(state.mask == 0); }
int main(void)
{
    prepare_pwm_program_mode(Mode_Standard, false);
    hal.coolant.set_state = coolant_off;
    CHECK(store_setting(Setting_RestoreOverrides, "1") == Status_OK);
    spindle_set_override(spindle_get(0), 150);
    CHECK(spindle_get(0)->param->override_pct == 150);
    CHECK(laser_block("M2") == Status_OK);
    CHECK(spindle_get(0)->param->override_pct == 100);
    CHECK(!laser_output_state.on);
    return EXIT_SUCCESS;
}
