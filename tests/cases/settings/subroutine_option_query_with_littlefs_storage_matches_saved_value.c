#include "support/setting_query_host.h"
int main(void)
{
    prepare_setting_query();
    /* Availability/readback unit; actual macro file execution has separate tests. */
    hal.driver_cap.littlefs = true;
    CHECK(store_setting(Setting_SubroutineOptions, "1") == Status_OK);
    check_integer_setting_query(Setting_SubroutineOptions, 1);
    CHECK(store_setting(Setting_SubroutineOptions, "0") == Status_OK);
    check_integer_setting_query(Setting_SubroutineOptions, 0);
    settings_init();
    check_integer_setting_query(Setting_SubroutineOptions, 0);
    return EXIT_SUCCESS;
}
