#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    CHECK(!spindle_select(3));
    CHECK(!spindle_select(-1));
    CHECK(spindle_get_default() == 0);
    CHECK(spindle_get_name(3) == NULL);
    CHECK(spindle_get_name(-1) == NULL);
    CHECK(spindle_enable(-1) == -1);
    CHECK(spindle_enable(3) == -1);
    CHECK(spindle_get_default() == 0);
    CHECK(spindle_config_calls[0] == 1);
    CHECK(spindle_config_calls[1] == 0 && spindle_config_calls[2] == 0);
    CHECK(!spindle_is_enabled(1) && !spindle_is_enabled(2));
    return EXIT_SUCCESS;
}
