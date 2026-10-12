#include "support/settings_validation_host.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    setting_detail_t detail = {.datatype = Format_RadioButtons, .format = "first,second,third"};
    char valid[] = "2", invalid[] = "3";
    CHECK(setting_validate_me(&detail, 2, valid) == Status_OK);
    CHECK(setting_validate_me(&detail, 3, invalid) == Status_SettingValueOutOfRange);
    return EXIT_SUCCESS;
}
