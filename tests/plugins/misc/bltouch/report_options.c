#include "bltouch_host.h"
#include <string.h>
int main(void)
{
#ifdef TEST_UNAVAILABLE
    claims_ok = false;
#endif
    load_bltouch();
    unsigned before = outputs;
    grbl.on_report_options(true);
    CHECK(option_calls == 1 && plugin_reports == 0);
    grbl.on_report_options(false);
    CHECK(option_calls == 2 && plugin_reports == 1 && outputs == before);
#ifdef TEST_UNAVAILABLE
    CHECK(strcmp(plugin_name, "BLTouch (N/A)") == 0 && warnings == 1);
#else
    CHECK(strcmp(plugin_name, "BLTouch") == 0 && warnings == 0);
#endif
    return 0;
}
