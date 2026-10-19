#include "support/boot_backlash_stream_host.h"
int main(void)
{
    prepare_backlash_stream(X_AXIS, false);
    CHECK(grbl_enter() == 0);
    check_backlash_stream(X_AXIS, false);
    return EXIT_SUCCESS;
}
