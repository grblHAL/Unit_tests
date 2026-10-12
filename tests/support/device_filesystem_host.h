#pragma once
#include "support/engine_host.h"
#include "support/backend_close.h"
#include "stream.h"
#include "check.h"

bool device_fs_add_stream(io_stream_properties_t *stream);
void fs_device_mount(void);
static unsigned device_claims;
static uint16_t device_pending;
static bool device_claim_fails;
static uint16_t device_rx_count(void) { return device_pending; }
static void device_write(const uint8_t *data, uint16_t length)
{
    (void)data;
    (void)length;
}
static const io_stream_t *device_claim(uint32_t baud)
{
    static const io_stream_t stream = {
        .write_n = device_write, .get_rx_buffer_count = device_rx_count
    };
    CHECK(baud == 115200);
    device_claims++;
    return device_claim_fails ? NULL : &stream;
}
static inline void register_device(stream_type_t type, uint8_t instance)
{
    io_stream_properties_t stream = {.type = type, .instance = instance, .claim = device_claim};
    stream.flags.claimable = stream.flags.modbus_ready = true;
    CHECK(device_fs_add_stream(&stream));
}
static inline void prepare_device_filesystem(void)
{
    engine_prepare();
    register_device(StreamType_Serial, 2);
    fs_device_mount();
}
