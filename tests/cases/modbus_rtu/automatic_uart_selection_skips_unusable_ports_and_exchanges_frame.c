#include "support/rtu_host.h"

static unsigned null_claims, invalid_claims, valid_claims;
static const io_stream_t *forbidden_claim(uint32_t baud)
{ (void)baud; CHECK(false); return NULL; }
static const io_stream_t *failed_claim(uint32_t baud)
{ CHECK(baud == 19200); null_claims++; return NULL; }
static const io_stream_t *invalid_claim(uint32_t baud)
{
    static io_stream_t invalid = {.type = StreamType_Serial};
    CHECK(baud == 19200); invalid_claims++; return &invalid;
}
static const io_stream_t *valid_claim(uint32_t baud)
{ valid_claims++; return claim_serial(baud); }
int main(void)
{
    engine_prepare();
    report_init_fns();
    hal.stream.is_connected = rtu_connected;
    hal.nvs.type = NVS_EEPROM;
    grbl.on_report_options = original_options;
    static io_stream_properties_t ports[] = {
        {.type = StreamType_Serial, .instance = 0, .flags = {.claimable = true}, .claim = forbidden_claim},
        {.type = StreamType_Serial, .instance = 1, .flags = {.claimable = true, .modbus_ready = true, .claimed = true}, .claim = forbidden_claim},
        {.type = StreamType_Serial, .instance = 2, .flags = {.claimable = true, .modbus_ready = true}, .claim = failed_claim},
        {.type = StreamType_Serial, .instance = 3, .flags = {.claimable = true, .modbus_ready = true}, .claim = invalid_claim},
        {.type = StreamType_Serial, .instance = 4, .flags = {.claimable = true, .modbus_ready = true}, .claim = valid_claim}
    };
    static io_stream_details_t streams = {.n_streams = 5, .streams = ports};
    stream_register_streams(&streams);
    modbus_rtu_init(-1, -2);
    CHECK(hal.driver_cap.modbus_rtu);
    CHECK(null_claims == 1 && invalid_claims == 1 && valid_claims == 1);
    setting_details_t *details = NULL;
    CHECK(setting_get_details(Settings_ModBus_BaudRate, &details) != NULL);
    CHECK(details != NULL && details->load != NULL);
    details->load();
    CHECK(modbus_isup().rtu);
    modbus_message_t message = {.tx_length = 8, .rx_length = 7,
        .crc_check = true, .adu = {1,3,0,0,0,1,0,0}};
    modbus_callbacks_t callbacks = {.on_rx_packet = received, .on_rx_exception = failed};
    CHECK(modbus_send(&message, &callbacks, false));
    poll_rtu(); poll_rtu();
    CHECK(tx_calls == 1);
    inject_reply(false); poll_rtu();
    CHECK(rx_calls == 1 && exceptions == 0);
    CHECK(reply.adu[3] == 0x12 && reply.adu[4] == 0x34);
    return EXIT_SUCCESS;
}
