#include "support/boot_host.h"
static stream_write_ptr write_all;
static unsigned arrivals, recoveries;
static void fault_after_welcome(const char *text)
{
    write_all(text);
    if(!arrivals && strstr(text, "GrblHAL")) {
        CHECK(!boot_control_signals.motor_fault && sys.alarm == Alarm_None);
        boot_control_signals.motor_fault = true;
        arrivals++;
    }
}
static void install_fault_arrival(settings_t *current)
{
    CHECK(current == &settings);
    hal.signals_cap.motor_fault = true;
    write_all = hal.stream.write_all;
    hal.stream.write_all = fault_after_welcome;
}
static void recover_after_rejected_command(void)
{
    if(boot_reads == 4) {
        CHECK(sys.alarm == Alarm_MotorFault && state_get() == STATE_ALARM);
        CHECK(!gc_state.modal.distance_incremental);
        CHECK(strstr(engine_output, "error:9") != NULL);
        boot_control_signals.motor_fault = false;
        recoveries++;
        boot_before_read = NULL;
    }
}
int main(void)
{
    boot_during_setup = install_fault_arrival;
    boot_before_read = recover_after_rejected_command;
    boot_program = "G91\n$X\n\x18" "$X\nG91\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(arrivals == 1 && recoveries == 1);
    CHECK(strstr(engine_output, "ALARM:17") != NULL);
    CHECK(strstr(engine_output, "error:79") != NULL);
    CHECK(strstr(engine_output, "Motor fault - clear, then reset to continue") != NULL);
    CHECK(gc_state.modal.distance_incremental && state_get() == STATE_IDLE);
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G21 G91") != NULL);
    CHECK(boot_release_calls == 1);
    return EXIT_SUCCESS;
}
