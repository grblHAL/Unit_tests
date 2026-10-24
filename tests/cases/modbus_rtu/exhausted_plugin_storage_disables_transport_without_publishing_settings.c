#include "support/rtu_host.h"
#include "nvs_buffer.h"

static uint32_t reserved_size;
static nvs_address_t reserved_address;
static unsigned reservations;
static void reserve_existing_plugin_storage(void)
{
    hal.nvs.type = NVS_EEPROM;
    /* Existing plugins reserve persistent records before the transport starts. */
    while(nvs_alloc(1))
        CHECK(++reservations < 8192);
    CHECK(reservations > 0);
    reserved_size = hal.nvs.driver_area.size;
    reserved_address = hal.nvs.driver_area.address;
}

int main(void)
{
    CHECK(!initialize_rtu_transport(NULL, -2, reserve_existing_plugin_storage));
    CHECK(!hal.driver_cap.modbus_rtu && !modbus_isup().rtu);
    CHECK(sys.alarm == Alarm_SelftestFailed);
    CHECK(hal.nvs.driver_area.size == reserved_size);
    CHECK(hal.nvs.driver_area.address == reserved_address);
    setting_details_t *details = NULL;
    CHECK(setting_get_details(Settings_ModBus_BaudRate, &details) == NULL);
    CHECK(grbl.on_report_options == original_options);
    for(unsigned i = 0; i < 20; i++)
        poll_rtu();
    CHECK(tx_calls == 0 && rx_calls == 0 && exceptions == 0);
    return EXIT_SUCCESS;
}
