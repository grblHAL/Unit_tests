#include "support/motion_program_host.h"
#include "support/settings_initialized_host.h"
#include "nvs.h"
static nvs_io_t original_nvs;
static unsigned failed_reads;
static bool fail_fixture_read(uint8_t *destination, uint32_t source, uint32_t size, bool checksum)
{
    uint32_t fixture = NVS_ADDR_PARAMETERS + CoordinateSystem_G59_3 * (sizeof(coord_system_data_t) + NVS_CRC_BYTES);
    if(source == fixture && size == sizeof(coord_system_data_t)) {
        failed_reads++;
        return false;
    }
    return original_nvs.memcpy_from_nvs(destination, source, size, checksum);
}
int main(void)
{
    prepare_motion_program();
    settings.version.id = SETTINGS_VERSION;
    hal.nvs.put_byte(0, SETTINGS_VERSION);
    settings_write_global();
    settings_init();
    gc_init(false);
    CHECK(grbl.tool_table.n_tools == 4);
    tool_data_t saved = {.tool_id = 3, .offset.values = {1, 2, 3}, .radius = 4};
    CHECK(host_save_tool(&saved));
    char fixture[] = "G10L2P9Z42";
    CHECK(gc_execute_block(fixture) == Status_OK);
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    original_nvs = hal.nvs;
    hal.nvs.memcpy_from_nvs = fail_fixture_read;
    char rejected[] = "G10L11P3Z2";
    CHECK(gc_execute_block(rejected) == Status_SettingReadFail);
    hal.nvs.memcpy_from_nvs = original_nvs.memcpy_from_nvs;
    CHECK(failed_reads == 1);
    CHECK(plan_get_current_block() == first && plan_get_block_buffer_available() == available);
    tool_data_t *tool = grbl.tool_table.get_tool(3)->data;
    CHECK(tool != NULL && tool->tool_id == 3);
    NEAR(tool->offset.x, 1); NEAR(tool->offset.y, 2); NEAR(tool->offset.z, 3);
    NEAR(tool->radius, 4);
    execute_motion_program();
    CHECK(physical_position[X_AXIS] == 80 && axis_pulses[X_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(protocol_execute_realtime());
    char restored[] = "G10L2P9Z42", retry[] = "G10L11P3Z2";
    CHECK(gc_execute_block(restored) == Status_OK);
    CHECK(gc_execute_block(retry) == Status_OK);
    tool = grbl.tool_table.get_tool(3)->data;
    CHECK(tool != NULL);
    NEAR(tool->offset.z, 40);
    NEAR(tool->radius, 4);
    CHECK(plan_get_current_block() == NULL && physical_position[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
