#include "support/system_metadata_host.h"
int main(void)
{
    prepare_system_metadata();
    stored_line_t first = "G20", second = "G91", recovered;
    settings_write_startup_line(0, first);
    settings_write_startup_line(1, second);
    for(unsigned slot = 0; slot < 2; slot++) {
        uint32_t checksum = NVS_ADDR_STARTUP_BLOCK + slot *
            (sizeof(stored_line_t) + NVS_CRC_BYTES) + sizeof(stored_line_t);
        hal.nvs.put_byte(checksum, hal.nvs.get_byte(checksum) ^ 1);
        metadata_output[0] = '\0';
        CHECK(system_command("$N") == Status_OK);
        char expected[96];
        if(slot == 0)
            snprintf(expected, sizeof(expected), "error:%u" ASCII_EOL "$N1=G91" ASCII_EOL,
                (unsigned)Status_SettingReadFail);
        else
            snprintf(expected, sizeof(expected), "$N0=" ASCII_EOL "error:%u" ASCII_EOL,
                (unsigned)Status_SettingReadFail);
        CHECK(strcmp(metadata_output, expected) == 0);
        CHECK(settings_read_startup_line(slot, recovered) && recovered[0] == '\0');
        CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
    }
    metadata_output[0] = '\0';
    CHECK(system_command("$N") == Status_OK);
    CHECK(strcmp(metadata_output, "$N0=" ASCII_EOL "$N1=" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
