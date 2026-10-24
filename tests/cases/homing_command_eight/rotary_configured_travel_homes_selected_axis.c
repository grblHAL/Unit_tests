#include "support/homing_command_host.h"

int main(void)
{
    prepare_homing_command();
    char rotary[] = "1", travel[] = "360";
    CHECK(settings_store_setting(Settings_RotaryAxes, rotary) == Status_OK);
    CHECK(settings_store_setting((setting_id_t)(Setting_AxisMaxTravel + A_AXIS), travel) == Status_OK);
    CHECK(settings.steppers.is_rotary.mask == (1u << A_AXIS));
    NEAR(settings.axis[A_AXIS].max_travel, -360);
    switch_position[A_AXIS] = 80;
    coord_data_t pulloff = {0};
    for(unsigned axis = 0; axis < N_AXIS; axis++) pulloff.values[axis] = .125f;
    limits_homing_pulloff(&pulloff);
    CHECK(execute_homing_command("$HA") == Status_OK);
    CHECK(homing_success && completed_calls == 1);
    CHECK(sys.homed.mask == (1u << A_AXIS));
    CHECK(physical_position[A_AXIS] == 70);
    CHECK(axis_pulses[A_AXIS] > 80 && wake_calls > 0);
    CHECK(sys.position[A_AXIS] == -10);
    for(unsigned axis = 0; axis < N_AXIS; axis++) if(axis != A_AXIS) {
        CHECK(axis_pulses[axis] == 0 && physical_position[axis] == 0);
        CHECK(sys.position[axis] == 0);
    }
    CHECK(plan_get_current_block() == NULL && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
