#pragma once
#include "support/ioports_pwm_host.h"
static xbar_t analog_pins[2][2] = {
    {{.id = 0, .function = Input_Analog_Aux0, .cap = {.input = true}},
     {.id = 1, .function = Input_Analog_Aux1, .cap = {.input = true}}},
    {{.id = 0, .function = Output_Analog_Aux0, .cap = {.output = true}},
     {.id = 1, .function = Output_Analog_Aux1, .cap = {.output = true}}}
};
static unsigned analog_output_calls;
static uint8_t analog_output_pin;
static float analog_output_value;
static bool analog_output_result = true;
static xbar_t *analog_pin_info(io_port_direction_t dir, uint8_t port)
{
    return port < 2 ? &analog_pins[dir][port] : NULL;
}
static void analog_description(io_port_direction_t dir, uint8_t port, const char *text)
{
    CHECK(port < 2 && text != NULL);
    analog_pins[dir][port].description = text;
}
static bool analog_output(uint8_t port, float value)
{
    CHECK(port < 2);
    analog_output_calls++;
    analog_output_pin = port;
    analog_output_value = value;
    return analog_output_result;
}
static inline void prepare_analog_ports(void)
{
    engine_prepare();
    analog_pins[Port_Output][0].config = configure_pwm;
    analog_pins[Port_Output][1].config = configure_pwm;
    static io_ports_data_t ports = {.in = {.n_ports = 2}, .out = {.n_ports = 2}};
    static io_analog_t analog = {.ports = &ports, .get_pin_info = analog_pin_info,
        .set_pin_description = analog_description, .analog_out = analog_output, .wait_on_input = pin_read};
    CHECK(ioports_add_analog(&analog));
}
