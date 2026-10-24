#include "support/settings_host.h"
#include "spindle_control.h"
static void keep_stopped(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    (void)spindle; (void)rpm;
    CHECK(!state.on);
}
static spindle_state_t read_stopped(spindle_ptrs_t *spindle)
{
    (void)spindle;
    return (spindle_state_t){0};
}
int main(void)
{
    engine_prepare();
    sys.cold_start = true;
    spindle_ptrs_t driver = {.type = SpindleType_VFD, .ref_id = 10,
        .rpm_min = 1, .rpm_max = 12000,
        .cap = {.enable = true, .variable = true, .at_speed = true, .rpm_range_locked = true},
        .set_state = keep_stopped, .get_state = read_stopped};
    CHECK(spindle_register(&driver, "Feedback VFD") == 0);
    CHECK(spindle_select(0));
    grbl.on_settings_changed = changed_settings;
    CHECK(!hal.driver_cap.spindle_encoder && spindle_get_caps(true).at_speed);
    const setting_detail_t *tolerance = setting_get_details(Setting_SpindleAtSpeedTolerance, NULL);
    CHECK(tolerance != NULL);
    CHECK(store_setting(Setting_SpindleAtSpeedTolerance, "2.5") == Status_OK);
    NEAR((float)atof(setting_get_value(tolerance, 0)), 2.5f);
    CHECK(store_setting(Setting_SpindleAtSpeedTolerance, "0") == Status_OK);
    NEAR((float)atof(setting_get_value(tolerance, 0)), 0);
    CHECK(change_callbacks == 2 && !spindle_get(0)->get_state(spindle_get(0)).on);
    CHECK(setting_get_details(Setting_SpindleAtSpeedTolerance, NULL) != NULL);
    return EXIT_SUCCESS;
}
