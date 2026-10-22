#include "support/boot_tool_position_reset_host.h"
#include "check.h"
static bool cancel_sent, cancel_marker, cancelled_jog_observed;
static unsigned cancel_input_calls;
static int32_t cancelled_jog_x;
static void cancel_manual_jog_input(void)
{
    cancel_input_calls++;
    cancel_marker = true;
}
static int32_t read_manual_jog(void)
{
    if(cancel_marker) {
        cancel_marker = false;
        return ASCII_CAN;
    }
    /* Sender transmits touch-off only after the cancelled jog returns to M6 wait. */
    if(strncmp(boot_program + boot_reads, "G10", 3) == 0 && !cancelled_jog_observed)
        return SERIAL_NO_DATA;
    return boot_tool_read();
}
static void service_manual_jog(sys_state_t state)
{
    boot_reset_during_tool_retract(state);
    if(state == STATE_JOG && boot_homing_timer_running) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        if(!cancel_sent && sys.position[X_AXIS] <= -200) {
            cancel_sent = true;
            CHECK(protocol_enqueue_realtime_command(CMD_JOG_CANCEL));
        }
    }
    if(cancel_sent && !cancel_marker && state_get() == STATE_TOOL_CHANGE &&
       plan_get_current_block() == NULL && !cancelled_jog_observed) {
        CHECK(HOST_PARSER_FLAGS.tool_change && gc_state.tool->tool_id == 0);
        cancelled_jog_observed = true;
        cancelled_jog_x = sys.position[X_AXIS];
        CHECK(cancelled_jog_x < -160 && cancelled_jog_x > -560);
        NEAR(gc_state.position[X_AXIS], (float)cancelled_jog_x / settings.axis[X_AXIS].steps_per_mm);
    }
}
static void install_manual_jog(void)
{
    install_boot_tool_positioning();
    hal.stream.read = read_manual_jog;
    hal.stream.cancel_read_buffer = cancel_manual_jog_input;
    grbl.on_execute_delay = service_manual_jog;
}
int main(void)
{
    prepare_boot_streamed_manual_change(true);
    boot_during_init = install_manual_jog;
    boot_on_realtime = service_manual_jog;
    boot_program = "$H\nG0X-2Y-3Z-1\nT3M6\n" "\xA3" "$J=G91X-5F100\nG10L2P1Z0\n" "\x81" "$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(cancel_sent && cancelled_jog_observed && cancel_input_calls == 1);
    CHECK(boot_tool_exit_sent && !boot_tool_reset_sent);
    CHECK(!HOST_PARSER_FLAGS.tool_change && gc_state.tool->tool_id == 3);
    CHECK(sys.position[X_AXIS] == -160 && sys.position[Y_AXIS] == -240 && sys.position[Z_AXIS] == -80);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        CHECK(sys.position[axis] == boot_motor_position[axis] - boot_tool_home_offset[axis]);
    CHECK(boot_tool_rt_handler == protocol_enqueue_realtime_command);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
