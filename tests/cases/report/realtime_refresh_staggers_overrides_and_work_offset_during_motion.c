#include "support/status_refresh_host.h"
int main(void)
{
    prepare_refresh_cycle();
    next_refresh_report();
    CHECK(strstr(engine_output, "|Ov:100,100,100") != NULL);
    CHECK(strstr(engine_output, "|WCO:") == NULL);
    next_refresh_report();
    CHECK(strstr(engine_output, "|WCO:0.000,0.000,0.000") != NULL);
    CHECK(strstr(engine_output, "|Ov:") == NULL);
    next_refresh_report();
    CHECK(strstr(engine_output, "|WCO:") == NULL && strstr(engine_output, "|Ov:") == NULL);
    CHECK(state_get() == STATE_CYCLE && plan_get_current_block() != NULL);
    finish_motion_pulses(); CHECK(protocol_exec_rt_system());
    CHECK(physical_position[X_AXIS] == 1600 && sys.position[X_AXIS] == 1600);
    return EXIT_SUCCESS;
}
