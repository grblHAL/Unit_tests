#include "support/reset_safety_host.h"
#include "check.h"

int main(void)
{
    prepare_reset_safety();
    system_set_exec_state_flag(EXEC_RESET);
    CHECK(!protocol_exec_rt_system());
    CHECK(sys.abort); CHECK(sys.reset_pending); CHECK(reset_driver_calls == 1);
    CHECK(reset_input_calls == 0); CHECK(coolant_calls == 1); CHECK(!actual_coolant.value);
    return EXIT_SUCCESS;
}
