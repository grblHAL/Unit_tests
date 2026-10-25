#include "support/build_report_host.h"

int main(void)
{
    prepare_build_report();
    for(unsigned pass = 0; pass < 3; pass++) {
        bool init_lock = pass == 1;
        char value[] = {init_lock ? '5' : '1', '\0'};
        CHECK(settings_store_setting(Setting_HomingEnable, value) == Status_OK);
        if(pass == 0) {
            char axes[] = "7";
            CHECK(settings_store_setting(Setting_HomingCycle_1, axes) == Status_OK);
        }
        CHECK(settings.homing.flags.enabled && settings.homing.flags.init_lock == init_lock);
        engine_output[0] = 0;
        build_options_calls = 0;
        build_report(true);
        CHECK(strstr(engine_output, ",HOME,") != NULL);
        const char *options = strstr(engine_output, "[OPT:");
        CHECK(options != NULL);
        options += 5;
        const char *end = strchr(options, ',');
        CHECK(end != NULL);
        CHECK((memchr(options, 'L', (size_t)(end - options)) != NULL) == !init_lock);
    }
    return EXIT_SUCCESS;
}
