#pragma once
#include "support/rtu_host.h"

static unsigned exception_service_calls, exception_attempt_ticks;
static bool exception_frame_injected;
static uint8_t device_exception;
static void service_device_exception(sys_state_t state)
{
    (void)state;
    CHECK(++exception_service_calls < 1000);
    poll_rtu();
    if(tx_calls && ++exception_attempt_ticks >= 2 && !exception_frame_injected) {
        uint8_t frame[] = {1, 0x83, device_exception, 0, 0};
        uint16_t crc = modbus_crc16x(frame, 3);
        frame[3] = (uint8_t)crc;
        frame[4] = (uint8_t)(crc >> 8);
        memcpy(rx_bytes, frame, sizeof(frame));
        rx_position = 0;
        rx_length = sizeof(frame);
        exception_frame_injected = true;
    }
}
static inline void request_device_exception(uint8_t code)
{
    device_exception = code;
    grbl.on_execute_realtime = service_device_exception;
    modbus_message_t message = {.tx_length = 8, .rx_length = 7, .crc_check = true,
        .adu = {1, 3, 0, 0, 0, 1, 0, 0}};
    modbus_callbacks_t callbacks = {.on_rx_packet = received, .on_rx_exception = failed};
    CHECK(!modbus_send(&message, &callbacks, true));
}
