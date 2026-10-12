#include "support/settings_validation_host.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    setting_detail_t detail = {.datatype = Format_String, .min_value = "2", .max_value = "4"};
    char short_text[] = "a", valid[] = "abcd", long_text[] = "abcde";
    CHECK(setting_validate_me(&detail, 0, short_text) == Status_SettingValueOutOfRange);
    CHECK(setting_validate_me(&detail, 0, valid) == Status_OK);
    CHECK(setting_validate_me(&detail, 0, long_text) == Status_SettingValueOutOfRange);
    return EXIT_SUCCESS;
}
