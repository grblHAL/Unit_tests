#include "support/settings_host.h"

int main(void)
{
    prepare_settings_store();
    char original[] = "Workshop router";
    CHECK(settings_write_build_info(original));
    uint32_t checksum_address = NVS_ADDR_BUILD_INFO + sizeof(stored_line_t);
    hal.nvs.put_byte(checksum_address, hal.nvs.get_byte(checksum_address) ^ 1);
    stored_line_t text = {0};
    CHECK(!settings_read_build_info(text));
    CHECK(settings_read_build_info(text));
    CHECK(text[0] == '\0');
    NEAR(settings.axis[X_AXIS].steps_per_mm, 80);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
