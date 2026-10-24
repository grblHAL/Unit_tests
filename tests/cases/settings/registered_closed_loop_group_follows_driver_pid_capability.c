#include "support/settings_host.h"

static const setting_group_detail_t pid_group[] = {
    {.id = Group_Spindle_ClosedLoop, .parent = Group_Spindle, .name = "Driver spindle feedback"}
};
static uint32_t driver_gain;
static unsigned saves;
static void driver_load(void) {}
static void driver_save(void) { saves++; }
static setting_detail_t gain_setting[] = {
    {.id = (setting_id_t)1001, .group = Group_Spindle_ClosedLoop, .name = "Feedback gain",
     .type = Setting_NonCore, .datatype = Format_Integer, .value = &driver_gain}
};
static setting_details_t pid_details = {.n_groups = 1, .groups = pid_group,
    .n_settings = 1, .settings = gain_setting, .load = driver_load,
    .restore = driver_load, .save = driver_save};
int main(void)
{
    prepare_settings_store();
    CHECK(!settings_is_group_available(Group_Spindle_ClosedLoop));
    CHECK(settings_register(&pid_details));
    const setting_group_detail_t *group = setting_get_group_details(Group_Spindle_ClosedLoop);
    CHECK(group == &pid_group[0] && group->parent == Group_Spindle);
    CHECK(!settings_is_group_available(Group_Spindle_ClosedLoop));
    hal.driver_cap.spindle_pid = true;
    CHECK(settings_is_group_available(Group_Spindle_ClosedLoop));
    CHECK(settings_is_group_available(Group_Spindle));
    CHECK(store_setting((setting_id_t)1001, "42") == Status_OK);
    CHECK(driver_gain == 42 && saves == 1);
    hal.driver_cap.spindle_pid = false;
    CHECK(!settings_is_group_available(Group_Spindle_ClosedLoop));
    CHECK(settings_is_group_available(Group_Spindle));
    return EXIT_SUCCESS;
}
