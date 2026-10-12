#include "support/engine_host.h"
#include "motion_control.h"
#include "protocol.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    state_set(STATE_IDLE);
    grbl.on_execute_realtime = protocol_execute_noop;
    plan_line_data_t data;
    plan_data_init(&data);
    data.feed_rate = 100;
    data.condition.target_validated = true;
    data.condition.target_valid = true;
    state_set(STATE_CHECK_MODE);
    float target[N_AXIS] = {3, 4, 0};
    CHECK(mc_line(target, &data) == Status_Handled);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
