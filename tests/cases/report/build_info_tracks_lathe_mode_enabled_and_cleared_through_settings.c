#include "support/build_report_host.h"
int main(void)
{
    prepare_build_report();
    char lathe[] = "2", normal[] = "0";
    CHECK(settings_store_setting(Setting_Mode, lathe) == Status_OK);
    build_report(true);
    CHECK(strstr(engine_output, ",LATHE") != NULL);
    CHECK(settings_store_setting(Setting_Mode, normal) == Status_OK);
    engine_output[0] = 0;
    build_report(true);
    CHECK(strstr(engine_output, ",LATHE") == NULL);
    CHECK(settings.mode == Mode_Standard && !gc_state.modal.diameter_mode);
    return EXIT_SUCCESS;
}
