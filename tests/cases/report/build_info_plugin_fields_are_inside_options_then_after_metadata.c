#include "support/build_report_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    build_plugin_output = true;
    build_report(true);
    CHECK(build_options_calls == 2);
    CHECK(build_options_phase[0] && !build_options_phase[1]);
    char *inline_field = strstr(engine_output, ",FIXTURE]" ASCII_EOL);
    char *firmware = strstr(engine_output, "[FIRMWARE:grblHAL]");
    char *plugin = strstr(engine_output, "[PLUGIN:fixture]" ASCII_EOL);
    CHECK(inline_field != NULL && firmware != NULL && plugin != NULL);
    CHECK(inline_field < firmware && firmware < plugin);
    return EXIT_SUCCESS;
}
