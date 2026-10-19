#include "support/spindle_broadcast_host.h"
int main(void)
{
    modal_spindle_direction[1] = false;
    start_clockwise_broadcast_fixture();
    check_rejected_broadcast("M4$-1", Status_GcodeUnsupportedCommand);
    return EXIT_SUCCESS;
}
