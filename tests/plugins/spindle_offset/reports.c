#include "offset_host.h"
int main(void)
{
    offset_prepare();
    grbl.on_report_options(true);
    grbl.on_report_options(false);
    CHECK(offset_reports == 2 && offset_plugins == 1);
    return 0;
}
