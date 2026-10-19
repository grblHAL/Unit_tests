#pragma once
#include "support/canned_motion_host.h"

static inline void prepare_corrupt_work_offset(void)
{
    prepare_canned_motion();
    coord_system_data_t saved = {0};
    saved.coord.x = 10;
    settings_write_coord_data(CoordinateSystem_G55, &saved);
    uint32_t checksum = NVS_ADDR_PARAMETERS + CoordinateSystem_G55 *
        (sizeof(saved) + NVS_CRC_BYTES) + sizeof(saved);
    hal.nvs.put_byte(checksum, hal.nvs.get_byte(checksum) ^ 1);
    CHECK(canned_block("G1X2F100") == Status_OK);
}
static inline void check_failed_work_offset_preserves_pending_cut(const char *command)
{
    plan_block_t *queued = plan_get_current_block();
    CHECK(queued != NULL);
    CHECK(canned_block(command) == Status_SettingReadFail);
    CHECK(plan_get_current_block() == queued && wake_calls == 0);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    NEAR(gc_state.modal.g5x_offset.data.coord.x, 0);
    NEAR(gc_state.position[X_AXIS], 2);
    coord_system_data_t restored;
    CHECK(settings_read_coord_data(CoordinateSystem_G55, &restored));
    NEAR(restored.coord.x, 0);
}
static inline void finish_work_offset_recovery(int32_t x)
{
    execute_motion_program();
    CHECK(physical_position[X_AXIS] == x && axis_pulses[X_AXIS] == (unsigned)x);
    CHECK(physical_position[Y_AXIS] == 0 && physical_position[Z_AXIS] == 0);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
}
