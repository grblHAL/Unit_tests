#pragma once
#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"
#include <string.h>
static xbar_t digital_pins[2][2] = {
    {{.id = 0, .function = Input_Aux0, .cap = {.input = true}},
     {.id = 1, .function = Input_Aux1, .cap = {.input = true}}},
    {{.id = 0, .function = Output_Aux0, .cap = {.output = true}},
     {.id = 1, .function = Output_Aux1, .cap = {.output = true}}}
};
static unsigned output_calls, read_calls;
static uint8_t physical_output, physical_input;
static bool output_value;
static bool output_log[16];
static uint8_t output_pin_log[16];
static wait_mode_t input_mode;
static float input_timeout;
static unsigned irq_calls;
static uint8_t irq_physical_port, irq_user_port;
static pin_irq_mode_t irq_mode;
static ioport_interrupt_callback_ptr irq_callback;
static bool pin_irq(uint8_t port, uint8_t user_port, pin_irq_mode_t mode, ioport_interrupt_callback_ptr callback)
{
    CHECK(port < 2);
    irq_physical_port = port;
    irq_user_port = user_port;
    irq_mode = mode;
    irq_callback = callback;
    irq_calls++;
    return true;
}
static xbar_t *pin_info(io_port_direction_t dir, uint8_t port)
{
    return port < 2 ? &digital_pins[dir][port] : NULL;
}
static void pin_description(io_port_direction_t dir, uint8_t port, const char *text)
{
    CHECK(port < 2 && text != NULL);
    digital_pins[dir][port].description = text;
}
static void pin_output(uint8_t port, bool value)
{
    CHECK(port < 2);
    physical_output = port;
    output_value = value;
    CHECK(output_calls < 16);
    output_log[output_calls] = value;
    output_pin_log[output_calls] = port;
    output_calls++;
}
static int32_t pin_read(uint8_t port, wait_mode_t mode, float timeout)
{
    CHECK(port < 2);
    physical_input = port;
    input_mode = mode;
    input_timeout = timeout;
    read_calls++;
    return 1;
}
static inline void register_ioports(void)
{
    static io_ports_data_t ports = {.in = {.n_ports = 2}, .out = {.n_ports = 2}};
    static io_digital_t digital = {.ports = &ports, .get_pin_info = pin_info,
        .set_pin_description = pin_description, .digital_out = pin_output,
        .wait_on_input = pin_read, .register_interrupt_handler = pin_irq};
    CHECK(ioports_add_digital(&digital));
}

static inline void prepare_ioports(void)
{
    engine_prepare();
    register_ioports();
}
