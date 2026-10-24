#include "support/build_report_host.h"

int main(void)
{
    prepare_build_report();
    for(unsigned enabled = 0; enabled < 3; enabled++) {
        bool allow_legacy = enabled == 1;
        char value[] = {allow_legacy ? '1' : '0', '\0'};
        CHECK(settings_store_setting(Setting_EnableLegacyRTCommands, value) == Status_OK);
        engine_output[0] = 0;
        build_options_calls = 0;
        build_report(true);
        CHECK(build_options_calls == 2 && build_options_phase[0] && !build_options_phase[1]);
        CHECK(strstr(engine_output, allow_legacy ? "[NEWOPT:ENUMS,RT+," : "[NEWOPT:ENUMS,RT-,") != NULL);
        CHECK(strstr(engine_output, allow_legacy ? "[NEWOPT:ENUMS,RT-," : "[NEWOPT:ENUMS,RT+,") == NULL);
        CHECK(settings.flags.legacy_rt_commands == allow_legacy);
    }
    return EXIT_SUCCESS;
}
