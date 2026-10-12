#include "support/settings_initialized_host.h"
#include "check.h"
static unsigned read_failures;
static size_t reported_bytes;
static status_code_t capture_status(status_code_t status) { CHECK(status == Status_SettingReadFail); read_failures++; return status; }
static void discard_report(const char *text) { reported_bytes += strlen(text); }
int main(void)
{
    prepare_initialized_settings(2.0f);
    settings.arc_tolerance = 0.9f;
    hal.nvs.put_byte(0, 0);
    grbl.report.status_message = capture_status;
    hal.stream.write = discard_report;
    change_callbacks = 0;
    settings_init();
    NEAR(settings.arc_tolerance, DEFAULT_ARC_TOLERANCE);
    CHECK(read_failures == 1 && reported_bytes > 0);
    CHECK(hal.nvs.get_byte(0) == SETTINGS_VERSION);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
