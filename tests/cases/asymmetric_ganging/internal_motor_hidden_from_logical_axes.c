#include "support/ganging_host.h"
#include "check.h"

int main(void)
{
    prepare_ganging();
    CHECK(system_n_axis() == 3);
    CHECK(system_axis_mask() == 7);
    return EXIT_SUCCESS;
}
