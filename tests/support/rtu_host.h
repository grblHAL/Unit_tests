#pragma once
#include "support/engine_host.h"
#include "modbus.h"
#include "crc.h"
#include "report.h"
#include "check.h"
#include <string.h>
void modbus_rtu_init(int8_t instance, int8_t direction);
static uint8_t tx_bytes[MODBUS_MAX_ADU_SIZE], rx_bytes[MODBUS_MAX_ADU_SIZE];
static uint16_t tx_length, rx_length, rx_position, pending_tx_bytes;
static unsigned tx_calls, rx_calls, exceptions;
static unsigned option_report_calls;
static bool option_report_new;
static bool rtu_connected(void) { return true; }
static void original_options(bool newopt) { option_report_calls++; option_report_new = newopt; }
static uint8_t exception_code;
static modbus_message_t reply;
static bool baud_rate(uint32_t baud) { CHECK(baud == 19200); return true; }
static uint16_t tx_count(void) { return pending_tx_bytes; }
static uint16_t rx_count(void) { return rx_length - rx_position; }
static int32_t read_serial(void) { return rx_position < rx_length ? rx_bytes[rx_position++] : SERIAL_NO_DATA; }
static void flush_tx(void) { }
static void flush_rx(void) { rx_position = rx_length = 0; }
static void write_serial(const uint8_t *bytes, uint16_t length)
{
    CHECK(length <= sizeof(tx_bytes));
    memcpy(tx_bytes, bytes, length);
    tx_length = length;
    tx_calls++;
}
static enqueue_realtime_command_ptr set_handler(enqueue_realtime_command_ptr handler)
{
    CHECK(handler != NULL);
    return NULL;
}
static void (*rtu_stream_direction)(bool);
static set_format_ptr rtu_stream_format;
static const io_stream_t *claim_serial(uint32_t baud)
{
    static io_stream_t serial = {.type = StreamType_Serial,
        .set_baud_rate = baud_rate, .get_tx_buffer_count = tx_count,
        .get_rx_buffer_count = rx_count, .read = read_serial, .write_n = write_serial,
        .reset_write_buffer = flush_tx, .reset_read_buffer = flush_rx,
        .set_enqueue_rt_handler = set_handler};
    CHECK(baud == 19200);
    serial.set_direction = rtu_stream_direction;
    serial.set_format = rtu_stream_format;
    return &serial;
}
static void received(modbus_message_t *message) { reply = *message; rx_calls++; }
static void failed(uint8_t code, void *context) { CHECK(context == NULL); exception_code = code; exceptions++; }
static inline bool initialize_rtu_transport(driver_reset_ptr reset, int8_t direction, void (*configure)(void))
{
    static io_stream_properties_t serial = {.type = StreamType_Serial, .instance = 0, .claim = claim_serial};
    static io_stream_details_t streams = {.n_streams = 1, .streams = &serial};
    engine_prepare();
    report_init_fns();
    hal.driver_reset = reset;
    if(configure) configure();
    hal.stream.is_connected = rtu_connected;
    grbl.on_report_options = original_options;
    hal.nvs.type = NVS_EEPROM;
    serial.flags.claimable = serial.flags.modbus_ready = true;
    stream_register_streams(&streams);
    modbus_rtu_init(0, direction);
    if(!hal.driver_cap.modbus_rtu) return false;
    setting_details_t *details = NULL;
    CHECK(setting_get_details(Settings_ModBus_BaudRate, &details) != NULL);
    CHECK(details != NULL && details->load != NULL);
    details->load();
    CHECK(modbus_isup().rtu);
    CHECK(tx_calls == 0 && rx_calls == 0 && exceptions == 0 && exception_code == 0);
    CHECK(tx_length == 0 && reply.rx_length == 0);
    return true;
}
static inline void prepare_rtu_transport(driver_reset_ptr reset, int8_t direction, void (*configure)(void))
{ CHECK(initialize_rtu_transport(reset, direction, configure)); }
static inline void prepare_rtu_with_reset(driver_reset_ptr reset)
{ prepare_rtu_transport(reset, -2, NULL); }
static inline void prepare_rtu(void) { prepare_rtu_with_reset(NULL); }
static inline void poll_rtu(void) { engine_ticks++; engine_execute_tasks(STATE_IDLE); }
static inline void send_request(void)
{
    modbus_message_t message = {.tx_length = 8, .rx_length = 7, .crc_check = true,
        .adu = {1, 3, 0, 0, 0, 1, 0, 0}};
    modbus_callbacks_t callbacks = {.on_rx_packet = received, .on_rx_exception = failed};
    CHECK(modbus_send(&message, &callbacks, false));
    poll_rtu();
    poll_rtu();
    CHECK(tx_calls == 1 && tx_length == 8);
    CHECK(tx_bytes[6] == 0x84 && tx_bytes[7] == 0x0a);
}
static inline void inject_reply(bool corrupt)
{
    uint8_t bytes[7] = {1, 3, 2, 0x12, 0x34, 0, 0};
    uint16_t crc = modbus_crc16x(bytes, 5);
    bytes[5] = (uint8_t)crc;
    bytes[6] = (uint8_t)(crc >> 8);
    if(corrupt) bytes[5] ^= 1;
    memcpy(rx_bytes, bytes, sizeof(bytes));
    rx_position = 0;
    rx_length = sizeof(bytes);
}

/* Current core resets Modbus through its public API before driver reset;
   legacy core chains transport reset through the driver callback. */
static inline void reset_rtu_driver(void)
{
#ifdef HOST_MODBUS_RESET_API
    modbus_reset(sys.abort);
#endif
    hal.driver_reset();
}
