#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_ResetActions, "5") == Status_OK);
    CHECK(!settings.homing.flags.keep_on_reset);
    CHECK(settings.flags.keep_offsets_on_reset);
    CHECK(!settings.flags.keep_rapids_override_on_reset);
    CHECK(settings.flags.keep_feed_override_on_reset);
    CHECK(change_callbacks == 1);
    const setting_detail_t *detail = setting_get_details(Setting_ResetActions, NULL);
    CHECK(detail && strcmp(setting_get_value(detail, 0), "5") == 0);
    CHECK(store_setting(Setting_ResetActions, "0") == Status_OK);
    CHECK(settings.homing.flags.keep_on_reset && settings.flags.keep_offsets_on_reset);
    CHECK(settings.flags.keep_rapids_override_on_reset && settings.flags.keep_feed_override_on_reset);
    CHECK(strcmp(setting_get_value(detail, 0), "0") == 0);
    CHECK(store_setting(Setting_ResetActions, "15") == Status_OK);
    CHECK(!settings.homing.flags.keep_on_reset && !settings.flags.keep_offsets_on_reset);
    CHECK(!settings.flags.keep_rapids_override_on_reset && !settings.flags.keep_feed_override_on_reset);
    CHECK(strcmp(setting_get_value(detail, 0), "15") == 0);
    CHECK(change_callbacks == 3);
    return EXIT_SUCCESS;
}
