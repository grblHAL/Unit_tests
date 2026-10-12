#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    CHECK(!spindle_select(3));
    CHECK(!spindle_select(-1));
    CHECK(spindle_get_default() == 0);
    CHECK(spindle_get_name(3) == NULL);
    return EXIT_SUCCESS;
}
