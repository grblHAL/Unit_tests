#include "support/spindle_broadcast_host.h"
int main(void)
{
    start_clockwise_broadcast_fixture();
    check_rejected_broadcast("M3$-2", Status_GcodeValueOutOfRange);
    return EXIT_SUCCESS;
}
