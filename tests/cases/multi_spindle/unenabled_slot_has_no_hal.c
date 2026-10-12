#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    CHECK(!spindle_is_enabled(1));
    CHECK(spindle_get(1) == NULL);
    CHECK(spindle_get(-1) == NULL);
    CHECK(spindle_get(2) == NULL);
    return EXIT_SUCCESS;
}
