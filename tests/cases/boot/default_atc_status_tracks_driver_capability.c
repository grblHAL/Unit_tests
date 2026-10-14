#include "support/boot_host.h"

int main(void)
{
    CHECK(grbl_enter() == 0);
    CHECK(hal.tool.atc_get_state() == ATC_None);
    hal.driver_cap.atc = true;
    CHECK(hal.tool.atc_get_state() == ATC_Online);
    hal.driver_cap.atc = false;
    CHECK(hal.tool.atc_get_state() == ATC_None);
    return EXIT_SUCCESS;
}
