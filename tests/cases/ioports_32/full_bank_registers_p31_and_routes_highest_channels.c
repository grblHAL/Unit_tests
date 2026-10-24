#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"
#include <string.h>

_Static_assert(Output_AuxMax - Output_Aux0 + 1 == 32, "32-output driver configuration required");
_Static_assert(Input_AuxMax - Input_Aux0 + 1 == 32, "32-input driver configuration required");
static xbar_t pins[2][32];
static unsigned output_calls, input_calls;
static uint8_t output_pin, input_pin;
static bool output_level;
static xbar_t *get_pin(io_port_direction_t dir, uint8_t port)
{ return port < 32 ? &pins[dir][port] : NULL; }
static void describe_pin(io_port_direction_t dir, uint8_t port, const char *text)
{ CHECK(port < 32); pins[dir][port].description = text; }
static void set_output(uint8_t port, bool level)
{ CHECK(port < 32); output_calls++; output_pin = port; output_level = level; }
static int32_t read_input(uint8_t port, wait_mode_t mode, float timeout)
{ CHECK(port < 32 && mode == WaitMode_Immediate && timeout == 0); input_calls++; input_pin = port; return 100 + port; }
int main(void)
{
    engine_prepare();
    for(unsigned dir = 0; dir < 2; dir++) for(unsigned port = 0; port < 32; port++) {
        pins[dir][port] = (xbar_t){.id = port,
            .function = (pin_function_t)((dir == Port_Input ? Input_Aux0 : Output_Aux0) + port)};
        pins[dir][port].cap.input = pins[dir][port].mode.input = dir == Port_Input;
        pins[dir][port].cap.output = pins[dir][port].mode.output = dir == Port_Output;
    }
    static io_ports_data_t data = {.in.n_ports = 32, .out.n_ports = 32};
    static io_digital_t driver = {.ports = &data, .get_pin_info = get_pin,
        .set_pin_description = describe_pin, .digital_out = set_output, .wait_on_input = read_input};
    CHECK(ioports_add_digital(&driver));
    CHECK(hal.port.num_digital_in == 32 && hal.port.num_digital_out == 32);
    CHECK(strcmp(pins[Port_Input][31].description, "P31") == 0);
    CHECK(strcmp(pins[Port_Output][31].description, "P31") == 0);
    CHECK(hal.port.get_pin_info(Port_Digital, Port_Input, 31) == &pins[Port_Input][31]);
    CHECK(ioport_wait_on_input(Port_Digital, 31, WaitMode_Immediate, 0) == 131);
    CHECK(input_calls == 1 && input_pin == 31);
    CHECK(ioport_digital_out(31, true));
    CHECK(output_calls == 1 && output_pin == 31 && output_level);
    CHECK(ioport_digital_out(31, false));
    CHECK(output_calls == 2 && output_pin == 31 && !output_level);
    CHECK(strcmp(pins[Port_Output][0].description, "P0") == 0);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 32);
    CHECK(ioports_unclaimed(Port_Digital, Port_Input) == 32);
    return EXIT_SUCCESS;
}
