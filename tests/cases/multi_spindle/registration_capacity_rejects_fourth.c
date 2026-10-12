#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    CHECK(spindle_register(&registered_spindles[0], "overflow") == -1);
    CHECK(spindle_get_count() == 3);
    return EXIT_SUCCESS;
}
