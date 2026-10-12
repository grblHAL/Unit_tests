#pragma once
#include "support/engine_host.h"
#include "stream.h"
#include "protocol.h"
#include "check.h"
#include <string.h>
static stream_rx_buffer_t receive_buffer;
static enqueue_realtime_command_ptr receive_handler;
static unsigned forwarded_calls, acknowledged_calls;
static uint8_t last_forwarded_byte;
static int32_t receive_read(void)
{
    return receive_buffer.head == receive_buffer.tail ? SERIAL_NO_DATA
         : receive_buffer.data[receive_buffer.tail];
}
static bool receive_realtime(uint8_t byte)
{
    last_forwarded_byte = byte;
    forwarded_calls++;
    return byte == CMD_STATUS_REPORT;
}
static enqueue_realtime_command_ptr receive_set_handler(enqueue_realtime_command_ptr handler)
{
    enqueue_realtime_command_ptr previous = receive_handler;
    receive_handler = handler;
    return previous;
}
static void receive_acknowledged(void) { acknowledged_calls++; }
static inline void prepare_stream_suspend(void)
{
    engine_prepare();
    memcpy(receive_buffer.data, "G0X1\n", 5);
    receive_buffer.head = 5;
    receive_handler = receive_realtime;
    hal.stream.read = receive_read;
    hal.stream.set_enqueue_rt_handler = receive_set_handler;
    grbl.on_toolchange_ack = receive_acknowledged;
}
