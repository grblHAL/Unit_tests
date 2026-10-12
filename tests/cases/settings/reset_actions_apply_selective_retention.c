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
    return EXIT_SUCCESS;
}
