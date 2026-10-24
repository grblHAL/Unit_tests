#include "support/motion_program_host.h"
#include "support/user_mcode_host.h"

static unsigned service_calls;
static user_mcode_type_t check_decimal(user_mcode_t code)
{
    user_check_calls++;
    return code == OpenPNP_SetJerk ? UserMCode_Normal : UserMCode_Unsupported;
}
static void service_motion(sys_state_t state)
{
    CHECK(++service_calls < 100000);
    if(state == STATE_CYCLE) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
}
static void execute_decimal(sys_state_t state, parser_block_t *block)
{
    CHECK(plan_get_current_block() == NULL && sys.position[X_AXIS] == 80);
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    execute_user_mcode(state, block);
}
int main(void)
{
    prepare_motion_program();
    install_user_mcodes();
    grbl.user_mcode.check = check_decimal;
    grbl.user_mcode.execute = execute_decimal;
    grbl.on_execute_realtime = service_motion;
    user_synchronized = true;
    user_claimed.x = user_claimed.y = user_claimed.z = true;
    queue_motion_program("G1X1F100");
    CHECK(user_mcode_block("M201.3X12Y13Z14") == Status_OK);
    CHECK(user_validate_calls == 1 && user_execute_calls == 1);
    CHECK(user_validated.user_mcode == OpenPNP_SetJerk && user_executed.user_mcode == OpenPNP_SetJerk);
    CHECK(user_execution_state == STATE_IDLE);
    NEAR(user_executed.values.xyz[X_AXIS], 12);
    NEAR(user_executed.values.xyz[Y_AXIS], 13);
    NEAR(user_executed.values.xyz[Z_AXIS], 14);
    NEAR(gc_state.position[X_AXIS], 1);
    NEAR(gc_state.position[Y_AXIS], 0);
    NEAR(gc_state.position[Z_AXIS], 0);
    NEAR(gc_state.feed_rate, 100);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(user_mcode_block("M201X5") == Status_GcodeUnsupportedCommand);
    CHECK(user_validate_calls == 1 && user_execute_calls == 1);
    CHECK(user_mcode_block("M201.30X3") == Status_OK);
    CHECK(user_validate_calls == 2 && user_execute_calls == 2);
    CHECK(user_executed.user_mcode == OpenPNP_SetJerk);
    NEAR(user_executed.values.xyz[X_AXIS], 3);
    CHECK(axis_pulses[X_AXIS] == 80 && axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
