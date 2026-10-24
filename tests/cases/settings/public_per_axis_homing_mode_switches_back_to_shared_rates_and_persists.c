#include "support/settings_initialized_host.h"
int main(void)
{
    prepare_initialized_settings(2);
    CHECK(store_setting(Setting_HomingEnable, "1") == Status_OK);
    CHECK(store_setting(Setting_HomingFeedRate, "25") == Status_OK);
    CHECK(store_setting(Setting_HomingSeekRate, "400") == Status_OK);
    CHECK(store_setting(Setting_HomingEnable, "513") == Status_OK);
    CHECK(settings.homing.flags.enabled && settings.homing.flags.per_axis_feedrates);
    const char *feeds[] = {"30", "35", "40"};
    const char *seeks[] = {"450", "550", "650"};
    for(unsigned axis = 0; axis < 3; axis++) {
        CHECK(store_setting(Setting_AxisHomingFeedRate + axis, feeds[axis]) == Status_OK);
        CHECK(store_setting(Setting_AxisHomingSeekRate + axis, seeks[axis]) == Status_OK);
    }
    settings_init();
    CHECK(settings.homing.flags.per_axis_feedrates);
    for(unsigned axis = 0; axis < 3; axis++) {
        NEAR(settings.axis[axis].homing_feed_rate, (float)(30 + 5 * axis));
        NEAR(settings.axis[axis].homing_seek_rate, (float)(450 + 100 * axis));
    }
    CHECK(store_setting(Setting_HomingEnable, "1") == Status_OK);
    CHECK(!settings.homing.flags.per_axis_feedrates);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        NEAR(settings.axis[axis].homing_feed_rate, 30);
        NEAR(settings.axis[axis].homing_seek_rate, 450);
    }
    unsigned before = change_callbacks;
    CHECK(setting_get_details(Setting_AxisHomingFeedRate + Y_AXIS, NULL) == NULL);
    CHECK(store_setting(Setting_AxisHomingFeedRate + Y_AXIS, "99") == Status_SettingDisabled);
    CHECK(change_callbacks == before);
    CHECK(store_setting(Setting_HomingFeedRate, "50") == Status_OK);
    CHECK(store_setting(Setting_HomingSeekRate, "700") == Status_OK);
    settings_init();
    CHECK(settings.homing.flags.enabled && !settings.homing.flags.per_axis_feedrates);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        NEAR(settings.axis[axis].homing_feed_rate, 50);
        NEAR(settings.axis[axis].homing_seek_rate, 700);
    }
    return EXIT_SUCCESS;
}
