#include "support/control_host.h"
#include "check.h"

int main(void)
{
    coord_data_t distance = {.values = {1, 2, 3}};
    coord_data_t *stored = limits_homing_pulloff(&distance); CHECK(stored != &distance);
    CHECK(limits_homing_pulloff(NULL) == stored); NEAR(stored->values[0], 1); NEAR(stored->values[2], 3);
    distance.values[0] = 99; NEAR(stored->values[0], 1);
    return EXIT_SUCCESS;
}
