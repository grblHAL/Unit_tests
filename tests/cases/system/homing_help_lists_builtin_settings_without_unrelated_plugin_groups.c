#include "support/system_metadata_host.h"
#include "support/settings_metadata_report_host.h"

int main(void)
{
    prepare_system_metadata();
    CHECK(settings_register(&metadata_details));
    float feed = settings.axis[X_AXIS].homing_feed_rate;
    CHECK(system_command("$HELP homing") == Status_OK);
    CHECK(strstr(metadata_output, "---- Homing:") != NULL);
    CHECK(strstr(metadata_output, "Homing cycle") != NULL);
    CHECK(strstr(metadata_output, "Homing direction invert") != NULL);
    CHECK(strstr(metadata_output, "Visible first") == NULL);
    CHECK(strstr(metadata_output, "Visible second") == NULL);
    CHECK(strstr(metadata_output, "N/A") == NULL);
    NEAR(settings.axis[X_AXIS].homing_feed_rate, feed);
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
