#include "support/multi_spindle_host.h"

static uint8_t selected_drivers[3] = {0, 2, 3};
static unsigned slot_saves;
static bool slot_available(const setting_detail_t *setting, uint_fast16_t offset)
{ (void)setting; return offset == 1 || offset == 2; }
static uint32_t get_slot(setting_id_t id)
{
    CHECK(id > Setting_SpindleEnable0 && id <= Setting_SpindleEnable0 + 2);
    return selected_drivers[id - Setting_SpindleEnable0];
}
static status_code_t set_slot(setting_id_t id, uint_fast16_t value)
{
    CHECK(id > Setting_SpindleEnable0 && id <= Setting_SpindleEnable0 + 2);
    CHECK(value <= 3);
    selected_drivers[id - Setting_SpindleEnable0] = (uint8_t)value;
    return Status_OK;
}
static setting_id_t normalize_slot(setting_id_t id)
{ return id > Setting_SpindleEnable0 && id <= Setting_SpindleEnable0 + 2 ? Setting_SpindleEnable0 : 0; }
static bool iterate_slots(const setting_detail_t *setting, setting_output_ptr callback, void *data)
{
    for(unsigned slot = 1; slot < 3; slot++)
        if(!callback(setting, slot, data)) return false;
    return true;
}
static void save_slots(void) { slot_saves++; }
static void load_slots(void) {}
static const setting_detail_t slot_setting = {
    .id = Setting_SpindleEnable0, .group = Group_Spindle, .name = "Enabled spindle",
    .datatype = Format_Int8, .type = Setting_NonCoreFn,
    .value = set_slot, .get_value = get_slot, .min_value = "0", .max_value = "3",
    .flags = {.increment = 1}, .is_available = slot_available
};
static setting_details_t slot_details = {
    .n_settings = 1, .settings = &slot_setting, .normalize = normalize_slot,
    .iterator = iterate_slots, .load = load_slots, .restore = load_slots, .save = save_slots
};
int main(void)
{
    prepare_multi_spindle();
    CHECK(settings_register(&slot_details));
    char third[] = "3", second[] = "2";
    CHECK(settings_store_setting((setting_id_t)(Setting_SpindleEnable0 + 1), third) == Status_OK);
    CHECK(settings_store_setting((setting_id_t)(Setting_SpindleEnable0 + 2), second) == Status_OK);
    CHECK(slot_saves == 2);
    CHECK(spindle_enable(2) == 1 && spindle_enable(1) == 2);
    CHECK(spindle_get(0)->id == 0 && spindle_get(1)->id == 2 && spindle_get(2)->id == 1);
    gc_init(false);
    hal.control.get_state = spindle_controls;
    hal.stream.is_connected = spindle_connected;
    report_init_fns(); report_init(); state_set(STATE_IDLE);
    CHECK(spindle_program_block("M3S3000$0") == Status_OK);
    CHECK(spindle_program_block("M4S5000$1") == Status_OK);
    CHECK(spindle_program_block("M3S7000$2") == Status_OK);
    NEAR(actual_spindle_rpm[0], 3000);
    NEAR(actual_spindle_rpm[2], 5000);
    NEAR(actual_spindle_rpm[1], 7000);
    CHECK(actual_spindle_states[0].on && actual_spindle_states[1].on && actual_spindle_states[2].on);
    CHECK(!actual_spindle_states[0].ccw && !actual_spindle_states[1].ccw && actual_spindle_states[2].ccw);
    CHECK(spindle_program_block("M5$1") == Status_OK);
    CHECK(!actual_spindle_states[2].on && actual_spindle_states[0].on && actual_spindle_states[1].on);
    CHECK(spindle_program_block("M5$-1") == Status_OK);
    for(unsigned id = 0; id < 3; id++) CHECK(!actual_spindle_states[id].on);
    CHECK(slot_saves == 2 && plan_get_current_block() == NULL);
    CHECK(state_get() == STATE_IDLE && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
