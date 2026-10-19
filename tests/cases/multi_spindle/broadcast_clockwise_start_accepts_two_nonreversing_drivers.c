#include "support/spindle_broadcast_host.h"
int main(void)
{
    modal_spindle_direction[0] = modal_spindle_direction[1] = false;
    start_clockwise_broadcast_fixture();
    CHECK(spindle_program_block("M5$-1") == Status_OK);
    CHECK(spindle_program_block("M3$-1") == Status_OK);
    check_broadcast_outputs(false);
    return EXIT_SUCCESS;
}
