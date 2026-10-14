#pragma once
#include "support/engine_host.h"
#include "stream.h"
#include "report.h"
#include "state_machine.h"
#include "check.h"
#include <string.h>
static char debug_output[512];
static unsigned debug_claim_calls, debug_drain_calls, debug_description_calls;
static uint32_t debug_baud;
static bool debug_reject_claim, debug_reenter;
static io_stream_properties_t debug_property;
static bool debug_connected(void) { return true; }
static uint16_t debug_tx_count(void) { debug_drain_calls++; return 0; }
static void debug_device_write(const char *text)
{
    CHECK(strlen(debug_output) + strlen(text) < sizeof(debug_output));
    strcat(debug_output, text);
    if(debug_reenter) { debug_reenter = false; debug_writeln("nested"); }
}
static const io_stream_t debug_device = {.type = StreamType_Serial, .instance = 0,
    .write = debug_device_write, .get_tx_buffer_count = debug_tx_count};
static const io_stream_t *debug_claim(uint32_t baud)
{
    debug_claim_calls++; debug_baud = baud;
    if(debug_reject_claim) return NULL;
    debug_property.flags.claimed = true;
    return &debug_device;
}
static void debug_describe(pin_function_t function, pin_group_t group, const char *description)
{
    CHECK(function == Output_TX); CHECK(group == PinGroup_UART);
    CHECK(strcmp(description, "Debug out") == 0); debug_description_calls++;
}
static inline void prepare_debug_serial(void)
{
    engine_prepare(); report_init_fns(); hal.stream.is_connected = debug_connected;
    debug_property = (io_stream_properties_t){.type = StreamType_Serial,
        .instance = 0, .flags = {.claimable = true}, .claim = debug_claim};
    static io_stream_details_t details = {.n_streams = 1, .streams = &debug_property};
    stream_register_streams(&details); hal.periph_port.set_pin_description = debug_describe;
}
static inline void start_debug_serial(void)
{
    prepare_debug_serial(); CHECK(debug_stream_init());
    debug_output[0] = 0; debug_drain_calls = 0;
}
