#include "support/hold_host.h"
#include "check.h"

int main(void)
{
    start_hold_move();
    CHECK(state_get_substate() == 0);
    return EXIT_SUCCESS;
}
