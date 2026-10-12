#include "support/reset_safety_host.h"
#include "check.h"

int main(void)
{
    prepare_reset_safety(); reset_controls.e_stop = true;
    system_set_exec_state_flag(EXEC_RESET);
    CHECK(protocol_exec_rt_system());
    CHECK(!sys.abort); CHECK(sys.alarm == Alarm_EStop); CHECK(state_get() == STATE_ESTOP);
    CHECK(reset_input_calls == 1); CHECK(reset_driver_calls == 1);
    CHECK(coolant_calls == 1); CHECK(!actual_coolant.value);
    CHECK(strstr(engine_output, "Emergency stop - clear, then reset to continue") != NULL);
    return EXIT_SUCCESS;
}
