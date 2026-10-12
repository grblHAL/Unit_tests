#pragma once
#include "support/io_motion_host.h"
static xbar_t analog_pins[2][2] = {
    {{.id = 0, .function = Input_Analog_Aux0, .cap = {.input = true, .analog = true}},
     {.id = 1, .function = Input_Analog_Aux1, .cap = {.input = true, .analog = true}}},
    {{.id = 0, .function = Output_Analog_Aux0, .cap = {.output = true, .analog = true}},
     {.id = 1, .function = Output_Analog_Aux1, .cap = {.output = true, .analog = true}}}
};
static unsigned analog_output_calls, analog_read_calls;
static uint8_t analog_output_port, analog_input_port;
static float analog_output_value;
static wait_mode_t analog_input_mode;
static bool analog_output(uint8_t port, float value)
{
    CHECK(port < 2);
    analog_output_port = port;
    analog_output_value = value;
    analog_output_calls++;
    return true;
}
static int32_t analog_read(uint8_t port, wait_mode_t mode, float timeout)
{
    CHECK(port < 2 && timeout == 0.0f);
    analog_input_port = port;
    analog_input_mode = mode;
    analog_read_calls++;
    return 123;
}
static xbar_t *analog_info(io_port_direction_t dir, uint8_t port)
{
    return port < 2 ? &analog_pins[dir][port] : NULL;
}
static void analog_description(io_port_direction_t dir, uint8_t port, const char *text)
{
    CHECK(port < 2 && text != NULL);
    analog_pins[dir][port].description = text;
}
static inline void prepare_analog_motion(void)
{
    prepare_io_motion();
    static io_ports_data_t ports = {.in = {.n_ports = 2}, .out = {.n_ports = 2}};
    static io_analog_t analog = {.ports = &ports, .analog_out = analog_output,
        .wait_on_input = analog_read, .get_pin_info = analog_info,
        .set_pin_description = analog_description};
    CHECK(ioports_add_analog(&analog));
}
