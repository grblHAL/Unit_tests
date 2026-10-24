#include "support/boot_homing_motion_host.h"
#include "planner.h"

static void install_unlimited_rotary_driver(void)
{
    install_boot_homing_driver();
    settings.steppers.is_rotary.mask = 1u << A_AXIS;
    settings.axis[A_AXIS].max_travel = 0;
    settings.homing.cycle[0].mask = 1u << A_AXIS;
    settings.limits.flags.jog_soft_limited = true;
    settings_write_global();
}
static void service_rotary_jog(sys_state_t state)
{
    (void)state;
    static bool jog_started;
    sys_state_t current = state_get();
    if(current == STATE_JOG) jog_started = true;
    boot_homing_foreground(current);
    if(boot_homing_timer_running && current == STATE_JOG)
        stepper_driver_interrupt_handler();
    if(jog_started && !boot_program[boot_reads] && state_get() == STATE_IDLE && plan_get_current_block() == NULL)
        boot_observe_fault_loop = false;
}
int main(void)
{
    prepare_boot_homing_motion();
    boot_during_init = install_unlimited_rotary_driver;
    boot_on_realtime = service_rotary_jog;
    boot_observe_fault_loop = true;
    boot_read_limit = 200000;
    boot_program = "$HA\n$J=G91A20F100\n";
    CHECK(grbl_enter() == 0);
    CHECK(sys.homed.mask == (1u << A_AXIS));
    CHECK(boot_motor_pulses[A_AXIS] == 230 + 1600);
    CHECK(boot_motor_position[A_AXIS] == 190 + 1600);
    CHECK(sys.position[A_AXIS] == -10 + 1600);
    NEAR(gc_state.position[A_AXIS], 19.875f);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        if(axis != A_AXIS) CHECK(boot_motor_pulses[axis] == 0);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
