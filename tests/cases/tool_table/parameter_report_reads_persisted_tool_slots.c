#include "support/settings_initialized_host.h"
#include "report.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    gc_init(false);
    report_init_fns();
    report_init();
    tool_data_t tool = {.tool_id = 2, .offset.values = {1, 2, 3}, .radius = 4};
    CHECK(host_save_tool(&tool));
    report_ngc_parameters();
    CHECK(strstr(engine_output, "[T:2|1.000,2.000,3.000|4.000|6,0,0||2]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
