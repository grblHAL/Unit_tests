#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    CHECK(spindle_get_hal(1, SpindleHAL_Raw) == &registered_spindles[1]);
    CHECK(spindle_get_hal(1, SpindleHAL_Active) == NULL);
    CHECK(spindle_enable(1) == 1);
    CHECK(spindle_get_hal(1, SpindleHAL_Active) == spindle_get(1));
    CHECK(spindle_get_hal(3, SpindleHAL_Configured) == NULL);
    return EXIT_SUCCESS;
}
