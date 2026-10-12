#include "support/settings_validation_host.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    setting_detail_t detail = {.datatype = Format_Integer, .min_value = "10", .flags = {.allow_null = true}};
    char text[] = "0";
    CHECK(setting_validate_me(&detail, 0, text) == Status_OK);
    return EXIT_SUCCESS;
}
