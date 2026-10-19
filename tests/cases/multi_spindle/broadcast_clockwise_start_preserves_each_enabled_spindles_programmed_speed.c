#include "support/spindle_broadcast_host.h"
int main(void)
{
    start_clockwise_broadcast_fixture();
    CHECK(spindle_program_block("M5$-1") == Status_OK);
    CHECK(!actual_spindle_states[0].on && !actual_spindle_states[1].on);
    CHECK(spindle_program_block("M3$-1") == Status_OK);
    check_broadcast_outputs(false);
    return EXIT_SUCCESS;
}
