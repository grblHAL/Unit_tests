#include "support/wall_host.h"
int main(void)
{
    prepare_wall();
    CHECK(sys.position[X_AXIS] == 0);
    CHECK(sys.position[Y_AXIS] == 16000);
    CHECK(sys.position[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
