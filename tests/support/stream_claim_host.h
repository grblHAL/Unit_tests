#pragma once
#include "support/engine_host.h"
#include "stream.h"
#include "protocol.h"
#include "check.h"
#include <string.h>
static io_stream_properties_t uart_property;
static io_stream_status_t uart_status;
static enqueue_realtime_command_ptr uart_handler;
static unsigned claim_calls, release_calls, handler_calls, description_calls;
static unsigned disable_calls, baud_calls, format_calls, read_reset_calls, write_reset_calls;
static uint32_t requested_baud;
static bool claim_fails, receive_disabled;
static serial_format_t requested_format;
static char uart_description[32];
static inline bool auxiliary_handler(uint8_t byte) { return byte == '?'; }
static enqueue_realtime_command_ptr uart_set_handler(enqueue_realtime_command_ptr handler)
{
    enqueue_realtime_command_ptr previous = uart_handler;
    uart_handler = handler;
    handler_calls++;
    return previous;
}
static bool uart_disable(bool disable) { receive_disabled = disable; disable_calls++; return true; }
static bool uart_baud(uint32_t baud) { requested_baud = uart_status.baud_rate = baud; baud_calls++; return true; }
static bool uart_format(serial_format_t format) { requested_format = format; format_calls++; return true; }
static void uart_read_reset(void) { read_reset_calls++; }
static void uart_write_reset(void) { write_reset_calls++; }
static const io_stream_t uart_device = {.type = StreamType_Serial, .instance = 1,
    .set_enqueue_rt_handler = uart_set_handler, .disable_rx = uart_disable,
    .set_baud_rate = uart_baud, .set_format = uart_format,
    .reset_read_buffer = uart_read_reset, .reset_write_buffer = uart_write_reset};
static const io_stream_t *uart_claim(uint32_t baud)
{
    claim_calls++;
    requested_baud = uart_status.baud_rate = baud;
    if(claim_fails) return NULL;
    CHECK(!uart_property.flags.claimed);
    uart_property.flags.claimed = uart_status.flags.claimed = true;
    return &uart_device;
}
static bool uart_release(uint8_t instance)
{
    CHECK(instance == 1);
    release_calls++;
    uart_property.flags.claimed = uart_status.flags.claimed = false;
    return true;
}
static const io_stream_status_t *uart_get_status(uint8_t instance) { CHECK(instance == 1); return &uart_status; }
static void uart_describe(pin_function_t function, pin_group_t group, const char *description)
{
    CHECK(function == Output_TX || function == Input_RX);
    CHECK(group == PinGroup_UART + 1);
    CHECK(strlen(description) < sizeof(uart_description));
    strcpy(uart_description, description);
    description_calls++;
}
static inline void prepare_stream_claim(void)
{
    engine_prepare();
    uart_property = (io_stream_properties_t){.type = StreamType_Serial, .instance = 1,
        .flags = {.claimable = true, .can_set_baud = true}, .claim = uart_claim,
        .release = uart_release, .get_status = uart_get_status};
    static io_stream_details_t details = {.n_streams = 1, .streams = &uart_property};
    stream_register_streams(&details);
    hal.periph_port.set_pin_description = uart_describe;
}
