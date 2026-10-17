#include "support/boot_fault_loop_host.h"
#include "support/boot_spindle_setup_host.h"
static unsigned rejected_calls, selected_calls;
static bool reject_spindle(spindle_ptrs_t *spindle)
{
    CHECK(spindle->id == 0);
    rejected_calls++;
    return false;
}
static void unexpected_selection(spindle_ptrs_t *spindle) { (void)spindle; selected_calls++; }
static void install_veto_and_startup_tasks(void)
{
    register_primary_during_init();
    register_fault_startup_tasks();
    grbl.on_spindle_select = reject_spindle;
    grbl.on_spindle_selected = unexpected_selection;
}
static void observe_veto_failure(sys_state_t state)
{
    CHECK(rejected_calls == 1 && selected_calls == 0);
    observe_startup_fault(state);
}
int main(void)
{
    boot_spindle_reference = 10;
    fault_expected_setup_calls = 1;
    boot_observe_fault_loop = true;
    boot_program = "";
    boot_during_init = install_veto_and_startup_tasks;
    boot_on_realtime = observe_veto_failure;
    (void)grbl_enter();
    CHECK(false);
    return EXIT_FAILURE;
}
