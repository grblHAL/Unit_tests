#include "support/spindle_broadcast_host.h"
int main(void)
{
    start_clockwise_broadcast_fixture();
    CHECK(spindle_program_block("M4$-1") == Status_OK);
    check_broadcast_outputs(true);
    return EXIT_SUCCESS;
}
