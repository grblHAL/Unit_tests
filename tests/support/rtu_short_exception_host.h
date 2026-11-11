#pragma once
#include "support/rtu_host.h"
#include "system.h"

static unsigned short_rx_calls, short_exceptions, short_timeouts;
static uint8_t short_code, short_context;

static void short_received(modbus_message_t *message)
{
    CHECK(message->context == &short_context);
    short_rx_calls++;
}
static void short_failed(uint8_t code, void *context)
{
    CHECK(context == &short_context);
    short_code = code;
    short_exceptions++;
}
static void short_timed_out(uint8_t code, void *context)
{
    CHECK(context == &short_context);
    (void)code;
    short_timeouts++;
}
static inline void start_short_exception_request(void)
{
    prepare_rtu();
    modbus_message_t message = {.context = &short_context, .tx_length = 8,
        .rx_length = 7, .crc_check = false, .adu = {1, 3, 0, 0, 0, 1, 0, 0}};
    modbus_callbacks_t callbacks = {.on_rx_packet = short_received,
        .on_rx_exception = short_failed, .on_rx_timeout = short_timed_out};
    CHECK(modbus_send(&message, &callbacks, false));
    poll_rtu();
    poll_rtu();
    CHECK(tx_calls == 1 && tx_length == 8);
}
static inline void make_short_exception(uint8_t frame[5])
{
    frame[0] = 1;
    frame[1] = 0x83;
    frame[2] = ModBus_IllegalDataAddress;
    uint16_t crc = modbus_crc16x(frame, 3);
    frame[3] = (uint8_t)crc;
    frame[4] = (uint8_t)(crc >> 8);
}
static inline void append_short_reply(const uint8_t *bytes, unsigned length)
{
    CHECK(rx_length + length <= sizeof(rx_bytes));
    memcpy(rx_bytes + rx_length, bytes, length);
    rx_length += length;
}
static inline void finish_short_exception(uint8_t expected_code)
{
    for(unsigned tick = 0; tick < 60; tick++) poll_rtu();
    CHECK(short_rx_calls == 0 && short_exceptions == 1 && short_timeouts == 0);
    CHECK(short_code == expected_code);
    CHECK(!modbus_isbusy());
    for(unsigned tick = 0; tick < 10; tick++) poll_rtu();
    CHECK(short_exceptions == 1 && short_timeouts == 0 && short_rx_calls == 0);
    engine_output[0] = '\0';
    char command[] = "$MODBUSSTATS";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(strstr(engine_output, "timeouts: 0") != NULL);
    CHECK(strstr(engine_output, expected_code == ModBus_CRCError ? "CRC errors: 1" : "CRC errors: 0") != NULL);
    CHECK(strstr(engine_output, expected_code == ModBus_CRCError ? "RX exceptions: 0" : "RX exceptions: 1") != NULL);
}
