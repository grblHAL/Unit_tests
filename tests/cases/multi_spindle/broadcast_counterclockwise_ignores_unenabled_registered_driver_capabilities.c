#include "support/spindle_broadcast_host.h"
int main(void)
{
    modal_spindle_direction[2] = false;
    start_clockwise_broadcast_fixture();
    CHECK(spindle_program_block("M4$-1") == Status_OK);
    check_broadcast_outputs(true);
    return EXIT_SUCCESS;
}
