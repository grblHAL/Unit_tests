#include "support/channel_settings_report_host.h"

int main(void)
{
    prepare_channel_settings_report();
    channel_mask = 0;
    report_grbl_settings(true, &reported_channels);
    CHECK(reported_channels == 0);
    channel_mask = 1;
    report_grbl_settings(true, &reported_channels);
    CHECK(reported_channels == 1 && channel_ids[0] == 1001);
    return EXIT_SUCCESS;
}
