#include "support/settings_validation_host.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    setting_detail_t detail = {.datatype = Format_Password, .min_value = "2", .max_value = "16"};
    char placeholder[] = PASSWORD_MASK;
    CHECK(!hal.stream.state.webui_connected);
    CHECK(setting_validate_me(&detail, 0, placeholder) == Status_OK);
    return EXIT_SUCCESS;
}
