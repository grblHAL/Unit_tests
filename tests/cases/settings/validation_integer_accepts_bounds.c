#include "support/settings_validation_host.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    setting_detail_t detail = {.datatype = Format_Integer, .min_value = "10", .max_value = "20"};
    char low[] = "10", high[] = "20";
    CHECK(setting_validate_me(&detail, 10, low) == Status_OK);
    CHECK(setting_validate_me(&detail, 20, high) == Status_OK);
    return EXIT_SUCCESS;
}
