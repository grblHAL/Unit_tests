#include "support/boot_backlash_stream_host.h"
int main(void)
{
    backlash_start_negative = true;
    prepare_backlash_stream(Z_AXIS, true);
    CHECK(grbl_enter() == 0);
    check_backlash_stream(Z_AXIS, true);
    return EXIT_SUCCESS;
}
