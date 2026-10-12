#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report(); settings.status_report.feed_speed = true;
    CHECK(!spindle_get(0)->cap.variable); realtime_report();
    CHECK(strstr(engine_output, "|F:0>") != NULL); CHECK(strstr(engine_output, "|FS:") == NULL);
    return EXIT_SUCCESS;
}
