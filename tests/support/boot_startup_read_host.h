#pragma once
#include "support/boot_host.h"
static nvs_io_t startup_nvs;
static unsigned startup_failed_slot, startup_record_failures;
static bool startup_record_fail_once = true, startup_records_captured;
static stored_line_t recovered_startup_records[2];
static void preload_second_startup_line(void)
{
    stored_line_t line = "G91";
    settings_write_startup_line(1, line);
}
static bool read_startup_with_one_failure(uint8_t *destination, uint32_t source, uint32_t size, bool checksum)
{
    uint32_t selected = NVS_ADDR_STARTUP_BLOCK + startup_failed_slot * (sizeof(stored_line_t) + NVS_CRC_BYTES);
    if(startup_record_fail_once && source == selected && size == sizeof(stored_line_t)) {
        startup_record_fail_once = false;
        startup_record_failures++;
        return false;
    }
    return startup_nvs.memcpy_from_nvs(destination, source, size, checksum);
}
static void install_startup_read_handler(settings_t *current)
{
    CHECK(current == &settings);
    startup_nvs = hal.nvs;
    hal.nvs.memcpy_from_nvs = read_startup_with_one_failure;
}
static void observe_recovered_startup_records(void)
{
    /* Startup execution is queued until the first realtime checkpoint. Do not
       consume its injected read failure from this observer beforehand. */
    if(!startup_record_failures) return;
    CHECK(settings_read_startup_line(0, recovered_startup_records[0]));
    CHECK(settings_read_startup_line(1, recovered_startup_records[1]));
    startup_records_captured = true;
    boot_before_read = NULL;
}
static void run_startup_record_failure(void)
{
    CHECK(N_STARTUP_LINE >= 2 && startup_failed_slot < 2);
    boot_startup_program = "G20";
    boot_during_init = preload_second_startup_line;
    boot_during_setup = install_startup_read_handler;
    boot_before_read = observe_recovered_startup_records;
    CHECK(grbl_enter() == 0);
    CHECK(sys.driver_started && sys.alarm == Alarm_None);
    CHECK(startup_record_failures == 1 && startup_records_captured);
    CHECK(recovered_startup_records[startup_failed_slot][0] == '\0');
    CHECK(strstr(engine_output, "error:7") != NULL && strstr(engine_output, "[GC:") != NULL);
}
