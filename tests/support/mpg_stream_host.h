#pragma once
#include "support/stream_connection_host.h"
#include "state_machine.h"
static io_stream_t mpg_primary;
static unsigned primary_resets, pendant_resets, registered_calls;
static bool primary_rx_disabled, pendant_rx_disabled, pendant_tx_capable;
static unsigned pendant_baud_calls;
static uint32_t pendant_baud;
static enqueue_realtime_command_ptr pendant_rt;
static char pendant_output[2048];
static int32_t primary_input(void) { return SERIAL_NO_DATA; }
static int32_t pendant_input(void) { return SERIAL_NO_DATA; }
static void reset_primary_input(void) { primary_resets++; }
static void reset_pendant_input(void) { pendant_resets++; }
static bool disable_primary_input(bool disable) { primary_rx_disabled = disable; return true; }
static bool disable_pendant_input(bool disable) { pendant_rx_disabled = disable; return true; }
static bool set_pendant_baud(uint32_t baud) { pendant_baud = baud; pendant_baud_calls++; return true; }
static enqueue_realtime_command_ptr set_pendant_handler(enqueue_realtime_command_ptr handler) { enqueue_realtime_command_ptr previous = pendant_rt; if(handler) pendant_rt = handler; return previous; }
static enqueue_realtime_command_ptr mpg_primary_handler(enqueue_realtime_command_ptr handler) { enqueue_realtime_command_ptr previous = primary_rt; if(handler) primary_rt = handler; return previous; }
static void write_pendant(const char *text) { CHECK(strlen(pendant_output) + strlen(text) < sizeof(pendant_output)); strcat(pendant_output, text); }
static void pendant_registered(io_stream_t *stream, bool tx_capable) { CHECK(stream->read == pendant_input); registered_calls++; pendant_tx_capable = tx_capable; }
static const io_stream_t pendant_device = {.type = StreamType_Serial, .instance = 1, .read = pendant_input, .write = write_pendant, .is_connected = stream_connected, .reset_read_buffer = reset_pendant_input, .disable_rx = disable_pendant_input, .set_enqueue_rt_handler = set_pendant_handler, .set_baud_rate = set_pendant_baud};
static inline void prepare_mpg_stream(void)
{
    prepare_report();
    state_set(STATE_IDLE);
    mpg_primary = primary_connection;
    mpg_primary.set_enqueue_rt_handler = mpg_primary_handler;
    pendant_rt = stream_mpg_check_enable;
    mpg_primary.read = primary_input;
    mpg_primary.reset_read_buffer = reset_primary_input;
    mpg_primary.disable_rx = disable_primary_input;
    CHECK(stream_connect(&mpg_primary));
    sys.driver_started = true;
    grbl.on_mpg_registered = pendant_registered;
}

static inline void pendant_send_text(const char *text)
{
    while(*text) CHECK(stream_mpg_check_enable((uint8_t)*text++));
}
