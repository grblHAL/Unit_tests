#include "offset_host.h"
int main(void)
{
    offset_storage = false;
    offset_prepare();
    CHECK(!offset_settings && !offset_moves);
    grbl.on_report_options(false);
    CHECK(offset_reports == 1 && !offset_plugins);
    return 0;
}
