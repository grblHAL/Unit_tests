#include "support/rtcp_host.h"
static unsigned read_calls;
static bool failed_read(uint8_t *dest, uint32_t source, uint32_t size, bool checksum)
{ (void)dest; (void)source; CHECK(size > 0 && checksum); read_calls++; return false; }

int main(void)
{
    prepare_rtcp();
    char offset[] = "12", length[] = "0.25";
    CHECK(settings_store_setting(Setting_Kinematics0, offset) == Status_OK);
    CHECK(settings_store_setting(Setting_Kinematics6, length) == Status_OK);
    setting_details_t *owner = NULL;
    CHECK(setting_get_details(Setting_Kinematics0, &owner) != NULL);
    hal.nvs.memcpy_from_nvs = failed_read;
    owner->load();
    CHECK(read_calls == 1);
    NEAR(setting_get_float_value(setting_get_details(Setting_Kinematics0, NULL), 0), 113.660f);
    NEAR(setting_get_float_value(setting_get_details(Setting_Kinematics6, NULL), 0), .5f);
    return EXIT_SUCCESS;
}
