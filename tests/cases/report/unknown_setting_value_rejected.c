#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    CHECK(report_grbl_setting((setting_id_t)9999, NULL) == Status_SettingDisabled);
    CHECK(engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
