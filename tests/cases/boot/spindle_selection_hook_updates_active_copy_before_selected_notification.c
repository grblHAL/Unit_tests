#include "support/boot_spindle_setup_host.h"
static unsigned selecting_calls, selected_calls;
static bool restrict_active_spindle(spindle_ptrs_t *spindle)
{
    CHECK(spindle->id == 0 && spindle->cap.direction);
    selecting_calls++;
    spindle->cap.direction = false;
    return true;
}
static void observe_selected_spindle(spindle_ptrs_t *spindle)
{
    CHECK(selecting_calls == 1 && selected_calls == 0);
    CHECK(spindle == spindle_get(0) && spindle->param->hal == spindle);
    CHECK(!spindle->cap.direction);
    selected_calls++;
}
static void install_spindle_selection_hooks(void)
{
    register_primary_during_init();
    grbl.on_spindle_select = restrict_active_spindle;
    grbl.on_spindle_selected = observe_selected_spindle;
}
int main(void)
{
    boot_spindle_reference = 10;
    boot_during_init = install_spindle_selection_hooks;
    boot_program = "M4S2000\n";
    CHECK(grbl_enter() == 0);
    CHECK(sys.driver_started && sys.alarm == Alarm_None);
    CHECK(selecting_calls == 1 && selected_calls == 1);
    CHECK(spindle_get_hal(0, SpindleHAL_Raw)->cap.direction);
    CHECK(!spindle_get(0)->cap.direction && !setup_spindle_states[0].on);
    CHECK(strstr(engine_output, "error:20") != NULL);
    return EXIT_SUCCESS;
}
