#pragma once
#include "support/engine_host.h"
#include "stream_passthru.h"
#include "check.h"
#include <string.h>
void task_execute_on_startup(void);
static enqueue_realtime_command_ptr uart_handler, usb_handler;
static uint8_t uart_input[160], uart_output[160], usb_output[160];
static uint16_t uart_input_length, uart_input_position, uart_output_length, usb_output_length;
static unsigned usb_chunks, cancelled;
static bool pin_values[2];
static xbar_t output_pins[2] = {
    {.id = 0, .function = Output_CoProc_Boot0, .cap = {.output = true}},
    {.id = 1, .function = Output_CoProc_Reset, .cap = {.output = true}}
};
static xbar_t *pin_info(io_port_direction_t dir, uint8_t port)
{
    return dir == Port_Output && port < 2 ? &output_pins[port] : NULL;
}
static void pin_description(io_port_direction_t dir, uint8_t port, const char *text)
{
    CHECK(dir == Port_Output && port < 2 && text != NULL);
}
static void pin_output(uint8_t port, bool value) { CHECK(port < 2); pin_values[port] = value; }
static enqueue_realtime_command_ptr uart_set_handler(enqueue_realtime_command_ptr handler)
{
    enqueue_realtime_command_ptr previous = uart_handler;
    uart_handler = handler;
    return previous;
}
static enqueue_realtime_command_ptr usb_set_handler(enqueue_realtime_command_ptr handler)
{
    enqueue_realtime_command_ptr previous = usb_handler;
    usb_handler = handler;
    return previous;
}
static bool uart_write(uint8_t byte)
{
    CHECK(uart_output_length < sizeof(uart_output));
    uart_output[uart_output_length++] = byte;
    return true;
}
static int32_t uart_read(void)
{
    return uart_input_position < uart_input_length ? uart_input[uart_input_position++] : SERIAL_NO_DATA;
}
static void uart_cancel(void) { cancelled++; }
static void usb_write(const uint8_t *bytes, uint16_t length)
{
    CHECK(usb_output_length + length <= sizeof(usb_output));
    memcpy(usb_output + usb_output_length, bytes, length);
    usb_output_length += length;
    usb_chunks++;
}
static const io_stream_t *claim_uart(uint32_t baud)
{
    static const io_stream_t uart = {.type = StreamType_Serial, .instance = 1,
        .read = uart_read, .write_char = uart_write, .set_enqueue_rt_handler = uart_set_handler,
        .cancel_read_buffer = uart_cancel};
    CHECK(baud == 115200);
    return &uart;
}
static inline void prepare_passthru(void)
{
    static io_ports_data_t ports = {.out = {.n_ports = 2}};
    static io_digital_t digital = {.ports = &ports, .get_pin_info = pin_info,
        .set_pin_description = pin_description, .digital_out = pin_output};
    static io_stream_properties_t uart = {.type = StreamType_Serial, .instance = 1,
        .flags = {.claimable = true}, .claim = claim_uart};
    static io_stream_details_t streams = {.n_streams = 1, .streams = &uart};
    engine_prepare();
    sys.cold_start = true;
    CHECK(ioports_add_digital(&digital));
    stream_register_streams(&streams);
    hal.stream.type = StreamType_Serial;
    hal.stream.state.is_usb = hal.stream.state.linestate_event = true;
    hal.stream.set_enqueue_rt_handler = usb_set_handler;
    hal.stream.write_n = usb_write;
}
static inline void start_passthru(void)
{
    stream_passthru_init(1, 115200, true);
    CHECK(hal.stream.state.passthru);
    sys.driver_started = true;
    task_execute_on_startup();
}
static inline void finish_passthru_startup(void)
{
    engine_ticks = 1250;
    engine_execute_tasks(STATE_IDLE);
    CHECK(cancelled == 1);
}
