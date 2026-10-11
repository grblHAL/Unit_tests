#include "support/boot_spindle_setup_host.h"
#include "check.h"
static uint8_t secondary_slot = 2;
static setting_detail_t slot_setting[] = {
    {.id = (setting_id_t)(Setting_SpindleEnable0 + 1), .group = Group_Spindle,
     .name = "Secondary spindle", .type = Setting_NonCore, .datatype = Format_Int8,
     .value = &secondary_slot}
};
static void slot_persistence(void) {}
static setting_details_t slot_details = {
    .n_settings = 1, .settings = slot_setting,
    .load = slot_persistence, .restore = slot_persistence, .save = slot_persistence
};
static void register_primary_and_slot_settings(void)
{
    register_primary_during_init();
    CHECK(settings_register(&slot_details));
}
static void register_and_enable_secondary(settings_t *current)
{
    register_setup_spindles(current);
    CHECK(spindle_select(0));
    CHECK(spindle_enable(1) == 1);
}
int main(void)
{
    boot_spindle_reference = 10;
    boot_during_init = register_primary_and_slot_settings;
    boot_during_setup = register_and_enable_secondary;
    boot_program = "$SPINDLESH\n";
    CHECK(grbl_enter() == 0);
    CHECK(sys.driver_started && sys.alarm == Alarm_None);
    CHECK(spindle_is_enabled(0) && spindle_is_enabled(1));
    CHECK(spindle_get(0)->id == 0 && spindle_get(1)->id == 1);
    CHECK(strstr(engine_output, "[SPINDLE:0|0|1|DR|primary|1000.0,12000.0]") != NULL);
    CHECK(strstr(engine_output, "[SPINDLE:1|1|1|DR|secondary|1000.0,12000.0]") != NULL);
    return EXIT_SUCCESS;
}
