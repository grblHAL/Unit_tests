#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    CHECK(spindle_enable(1) == 1);
    CHECK(spindle_enable(2) == -1);
    CHECK(spindle_get_default() == 0 && spindle_get(1)->id == 1);
    return EXIT_SUCCESS;
}
