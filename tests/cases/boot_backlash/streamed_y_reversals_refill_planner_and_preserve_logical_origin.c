#include "support/boot_backlash_stream_host.h"
int main(void)
{
    prepare_backlash_stream(Y_AXIS, true);
    CHECK(grbl_enter() == 0);
    check_backlash_stream(Y_AXIS, true);
    return EXIT_SUCCESS;
}
