#pragma once
#include "support/report_host.h"
#include "stream.h"
static io_stream_status_t port_status;
static bool uart_status_available = true;
static const io_stream_status_t *get_port_status(uint8_t instance)
{
    CHECK(instance == 1);
    return uart_status_available ? &port_status : NULL;
}
static inline bool report_character(uint8_t c)
{
    char text[2] = {(char)c, 0};
    hal.stream.write(text);
    return true;
}
static xbar_t uart_pins[] = {
    {.pin = 9, .function = Output_TX, .group = PinGroup_UART2, .port = "PA", .description = "Pendant"},
    {.pin = 10, .function = Input_RX, .group = PinGroup_UART2, .port = "PA", .description = "Pendant"},
    {.pin = 4, .function = Output_StepX, .group = PinGroup_StepperStep, .port = "PB"}
};
static unsigned uart_pin_count = 3;
static inline void enumerate_uart_pins(bool low_level, pin_info_ptr callback, void *data)
{
    CHECK(!low_level);
    for(unsigned i = 0; i < uart_pin_count; i++) callback(&uart_pins[i], data);
}
static void prepare_uart_report(void)
{
    prepare_report();
    static io_stream_properties_t port = {.type = StreamType_Serial, .instance = 1, .get_status = get_port_status};
    static io_stream_details_t details = {.n_streams = 1, .streams = &port};
    stream_register_streams(&details);
}
