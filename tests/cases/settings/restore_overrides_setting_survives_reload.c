#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2.0f);
    const setting_detail_t *detail = setting_get_details(Setting_RestoreOverrides, NULL);
    CHECK(detail != NULL);
    unsigned combinations = detail->datatype == Format_Bitfield ? 4 : 2;
    for(unsigned actions = 0; actions < combinations; actions++) {
        char value[] = {(char)('0' + actions), '\0'};
        CHECK(store_setting(Setting_RestoreOverrides, value) == Status_OK);
        CHECK(settings.flags.restore_overrides == (actions & 1));
        settings.flags.restore_overrides = !(actions & 1);
        settings_init();
        CHECK(settings.flags.restore_overrides == (actions & 1));
        CHECK(strcmp(setting_get_value(detail, 0), value) == 0);
    }
    return EXIT_SUCCESS;
}
