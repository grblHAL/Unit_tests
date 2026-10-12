#include "support/hold_host.h"
#include "check.h"

int main(void)
{
    start_hold_move();
    hold_motion();
    CHECK(sys.position[X_AXIS] > 0);
    CHECK(sys.position[X_AXIS] < 1600);
    CHECK(sys.position[Y_AXIS] == 0);
    CHECK(wake_calls == 1);
    return EXIT_SUCCESS;
}
