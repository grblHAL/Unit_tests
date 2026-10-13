#include "support/channel_settings_report_host.h"

int main(void)
{
    prepare_channel_settings_report();
    report_grbl_settings(true, &reported_channels);
    CHECK(reported_channels == 2);
    CHECK(channel_ids[0] == 1003 && channel_ids[1] == 1005);
    return EXIT_SUCCESS;
}
