#include "select_host.h"
#include <string.h>
int main(void)
{
    select_prepare();
    CHECK(spindle_select(0));
    grbl.on_report_options(false);
    CHECK(strstr(select_output, "[SPINDLE:Primary]"));
    select_output[0] = 0;
    grbl.on_report_options(true);
    CHECK(!*select_output);
    return 0;
}
