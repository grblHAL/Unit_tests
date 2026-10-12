#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    CHECK(spindle_get_default() == 0);
    CHECK(spindle_is_enabled(0));
    CHECK(spindle_config_calls[0] == 1);
    CHECK(spindle_select(0));
    CHECK(spindle_config_calls[0] == 1);
    return EXIT_SUCCESS;
}
