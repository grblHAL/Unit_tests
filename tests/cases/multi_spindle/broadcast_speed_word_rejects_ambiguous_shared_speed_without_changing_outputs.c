#include "support/spindle_broadcast_host.h"
int main(void)
{
    start_clockwise_broadcast_fixture();
    check_rejected_broadcast("M3S5000$-1", Status_NegativeValue);
    return EXIT_SUCCESS;
}
