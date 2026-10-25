#include "led_host.h"
int main(void)
{
    led_prepare();
    display_init();
    grbl.on_report_options(true);
    CHECK(led_reports == 1 && led_plugins == 0);
    grbl.on_report_options(false);
    CHECK(led_reports == 2 && led_plugins == 1);
    return 0;
}
