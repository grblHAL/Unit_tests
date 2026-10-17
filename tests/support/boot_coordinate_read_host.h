#pragma once
#include "support/boot_host.h"
static nvs_io_t coordinate_nvs;
static coord_system_id_t coordinate_failed_record;
static bool coordinate_fail_once;
static bool coordinate_g92_volatile;
static unsigned coordinate_read_failures, coordinate_wco_notifications;
static float coordinate_saved_g54, coordinate_saved_g92, coordinate_seen_g54, coordinate_seen_g92;
static coord_system_data_t coordinate_record_g54, coordinate_record_g55, coordinate_record_g92;
static bool coordinate_records_captured;
static void capture_recovered_coordinates(void)
{
    /* grbl_enter frees its NVS buffer on return. Inspect records while the
       controller is alive, before the sender's first query. */
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &coordinate_record_g54));
    CHECK(settings_read_coord_data(CoordinateSystem_G55, &coordinate_record_g55));
    CHECK(settings_read_coord_data(CoordinateSystem_G92, &coordinate_record_g92));
    coordinate_records_captured = true;
    boot_before_read = NULL;
}
static void observe_cold_work_offsets(void)
{
    coordinate_wco_notifications++;
    coordinate_seen_g54 = gc_state.modal.g5x_offset.data.coord.x;
    coordinate_seen_g92 = gc_state.g92_offset.coord.x;
}
static void preload_work_coordinates(void)
{
    settings.flags.g92_is_volatile = coordinate_g92_volatile;
    settings_write_global();
    coord_system_data_t record = {0};
    record.coord.x = coordinate_saved_g54;
    settings_write_coord_data(CoordinateSystem_G54, &record);
    record.coord.x = 7;
    settings_write_coord_data(CoordinateSystem_G55, &record);
    record.coord.x = coordinate_saved_g92;
    settings_write_coord_data(CoordinateSystem_G92, &record);
    grbl.on_wco_changed = observe_cold_work_offsets;
}
static bool read_coordinates_with_one_failure(uint8_t *destination, uint32_t source, uint32_t size, bool checksum)
{
    uint32_t selected = NVS_ADDR_PARAMETERS + coordinate_failed_record * (sizeof(coord_system_data_t) + NVS_CRC_BYTES);
    if(coordinate_fail_once && source == selected && size == sizeof(coord_system_data_t)) {
        coordinate_fail_once = false;
        coordinate_read_failures++;
        return false;
    }
    return coordinate_nvs.memcpy_from_nvs(destination, source, size, checksum);
}
static void install_coordinate_read_handler(settings_t *current)
{
    CHECK(current == &settings);
    coordinate_nvs = hal.nvs;
    hal.nvs.memcpy_from_nvs = read_coordinates_with_one_failure;
}
static void run_coordinate_boot(void)
{
    boot_during_init = preload_work_coordinates;
    boot_during_setup = install_coordinate_read_handler;
    boot_program = "$#\n";
    boot_before_read = capture_recovered_coordinates;
    CHECK(grbl_enter() == 0);
    CHECK(sys.driver_started && sys.alarm == Alarm_None);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(coordinate_records_captured);
    NEAR(coordinate_record_g55.coord.x, 7);
    CHECK(gc_state.position[X_AXIS] == 0 && sys.position[X_AXIS] == 0);
}
