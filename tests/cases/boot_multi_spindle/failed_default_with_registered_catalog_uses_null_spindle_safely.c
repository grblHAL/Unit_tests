#include "support/boot_host.h"
#include "spindle_control.h"

static unsigned config_calls[2], physical_outputs;
static bool null_running_seen;
static bool unavailable_driver(spindle_ptrs_t *spindle)
{
    CHECK(spindle->id >= 0 && spindle->id < 2);
    config_calls[spindle->id]++;
    return false;
}
static void physical_output(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{ (void)spindle; (void)state; (void)rpm; physical_outputs++; }
static spindle_state_t physical_state(spindle_ptrs_t *spindle)
{ (void)spindle; return (spindle_state_t){0}; }
static void register_catalog(void)
{
    static const spindle_ptrs_t drivers[] = {
        {.type = SpindleType_Basic, .ref_id = 10, .cap.direction = true,
         .config = unavailable_driver, .set_state = physical_output, .get_state = physical_state},
        {.type = SpindleType_Basic, .ref_id = 20, .cap.direction = true,
         .config = unavailable_driver, .set_state = physical_output, .get_state = physical_state}
    };
    CHECK(spindle_register(&drivers[0], "unavailable primary") == 0);
    CHECK(spindle_register(&drivers[1], "unavailable secondary") == 1);
}
static void observe_null_spindle(void)
{
    if(boot_reads == strlen("M3S500\n")) {
        spindle_ptrs_t *active = spindle_get(0);
        CHECK(active && active->type == SpindleType_Null && active->id == 2);
        CHECK(active->get_state(active).on);
        CHECK(physical_outputs == 0);
        null_running_seen = true;
    }
}
int main(void)
{
    boot_spindle_reference = 10;
    boot_during_init = register_catalog;
    boot_before_read = observe_null_spindle;
    boot_program = "M3S500\nM5\n$SPINDLESH\n";
    CHECK(grbl_enter() == 0);
    CHECK(sys.driver_started && sys.alarm == Alarm_None && state_get() == STATE_IDLE);
    CHECK(null_running_seen && physical_outputs == 0);
    CHECK(config_calls[0] == 1 && config_calls[1] == 0);
    CHECK(spindle_get_default() == 2 && spindle_get_count() == 3);
    CHECK(spindle_add_null() == 2 && spindle_get_count() == 3);
    spindle_ptrs_t *active = spindle_get(0);
    CHECK(active && active->type == SpindleType_Null && !active->get_state(active).on);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
