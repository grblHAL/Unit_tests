#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"
#include <string.h>
static xbar_t pins[2][12];
static uint8_t output_pin;
static bool output_level;
static xbar_t *get_info(io_port_direction_t direction, uint8_t port)
{ return port < 12 ? &pins[direction][port] : NULL; }
static void describe(io_port_direction_t direction, uint8_t port, const char *name)
{ CHECK(port < 12); pins[direction][port].description = name; }
static void output(uint8_t port, bool level)
{ CHECK(port < 12); output_pin = port; output_level = level; }
static int32_t input(uint8_t port, wait_mode_t mode, float timeout)
{ CHECK(port < 12 && mode == WaitMode_Immediate && timeout == 0); return 100 + port; }
int main(void)
{
    engine_prepare();
    for(unsigned direction = 0; direction < 2; direction++) for(unsigned port = 0; port < 12; port++) {
        pins[direction][port] = (xbar_t){.id = port,
            .function = (pin_function_t)((direction == Port_Input ? Input_Aux0 : Output_Aux0) + port)};
        pins[direction][port].cap.input = direction == Port_Input;
        pins[direction][port].cap.output = direction == Port_Output;
    }
    io_ports_data_t data = {.in.n_ports = 12, .out.n_ports = 12};
    io_digital_t driver = {.ports = &data, .get_pin_info = get_info,
        .set_pin_description = describe, .digital_out = output, .wait_on_input = input};
    CHECK(ioports_add_digital(&driver));
    CHECK(hal.port.num_digital_in == 12 && hal.port.num_digital_out == 12);
    for(unsigned direction = 0; direction < 2; direction++) {
        CHECK(strcmp(pins[direction][9].description, "P9") == 0);
        CHECK(strcmp(pins[direction][10].description, "P10") == 0);
        CHECK(strcmp(pins[direction][11].description, "P11") == 0);
    }
    CHECK(ioport_remap(Port_Digital, Port_Output, 0, 10));
    CHECK(strcmp(pins[Port_Output][10].description, "P0") == 0);
    hal.port.digital_out(0, true); CHECK(output_pin == 10 && output_level);
    hal.port.digital_out(10, false); CHECK(output_pin == 0 && !output_level);
    CHECK(ioport_remap(Port_Digital, Port_Input, 1, 11));
    CHECK(ioport_wait_on_input(Port_Digital, 1, WaitMode_Immediate, 0) == 111);
    CHECK(ioport_wait_on_input(Port_Digital, 11, WaitMode_Immediate, 0) == 101);
    uint8_t plugin_port = 0; /* Claim consumes the physical auxiliary number. */
    CHECK(ioport_claim(Port_Digital, Port_Output, &plugin_port, "Plugin output"));
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 11);
    CHECK(strcmp(pins[Port_Output][0].description, "Plugin output") == 0);
    hal.port.digital_out(plugin_port, true); CHECK(output_pin == 0 && output_level);
    hal.port.digital_out(10, false); CHECK(output_pin == 11 && !output_level);
    hal.port.digital_out(0, true); CHECK(output_pin == 10 && output_level);
    CHECK(ioports_unclaimed(Port_Digital, Port_Input) == 12);
    return EXIT_SUCCESS;
}
