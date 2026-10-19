#include "support/setting_query_host.h"
int main(void)
{
    prepare_setting_query();
    hal.signals_cap.e_stop = true;
    CHECK(store_setting(Setting_UnlockAfterEStop, "0") == Status_OK);
    check_integer_setting_query(Setting_UnlockAfterEStop, 0);
    CHECK(store_setting(Setting_UnlockAfterEStop, "1") == Status_OK);
    check_integer_setting_query(Setting_UnlockAfterEStop, 1);
    settings_init();
    check_integer_setting_query(Setting_UnlockAfterEStop, 1);
    return EXIT_SUCCESS;
}
