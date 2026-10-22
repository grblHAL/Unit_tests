#include "support/engine_host.h"
#include "spindle_control.h"
#include "check.h"

static bool unexpected_spindle(spindle_info_t *spindle, void *data)
{
    (void)spindle; (void)data;
    CHECK(false);
    return true;
}

int main(void)
{
    engine_prepare();
    CHECK(!spindle_enumerate_spindles(NULL, NULL));
    CHECK(!spindle_enumerate_spindles(unexpected_spindle, NULL));
    CHECK(spindle_get_caps(false).value == 0);
    CHECK(spindle_get_caps(true).value == 0);
    return EXIT_SUCCESS;
}
