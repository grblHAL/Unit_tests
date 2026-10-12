#include "support/hold_host.h"
#include "check.h"

int main(void)
{
    start_hold_move();
    sys.probing_state = Probing_Active;
    CHECK(state_get_substate() == 2);
    return EXIT_SUCCESS;
}
