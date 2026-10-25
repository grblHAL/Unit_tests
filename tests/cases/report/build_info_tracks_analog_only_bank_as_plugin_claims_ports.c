#include "support/build_report_host.h"
#include "support/ioports_analog_host.h"

static void options(bool extended) { (void)extended; }
static void describe_bank(void)
{
    char description[] = "analog controller";
    engine_output[0] = 0;
    report_build_info(description, true);
}
int main(void)
{
    prepare_build_report();
    grbl.on_report_options = options;
    analog_pins[Port_Output][0].config = configure_pwm;
    analog_pins[Port_Output][1].config = configure_pwm;
    static io_ports_data_t ports = {.in = {.n_ports = 2}, .out = {.n_ports = 2}};
    static io_analog_t analog = {.ports = &ports, .get_pin_info = analog_pin_info,
        .set_pin_description = analog_description, .analog_out = analog_output,
        .wait_on_input = pin_read};
    CHECK(ioports_add_analog(&analog));
    describe_bank();
    CHECK(strstr(engine_output, "[AUX IO:0,0,2,2]" ASCII_EOL) != NULL);
    for(unsigned i = 0; i < 2; i++) {
        uint8_t port = (uint8_t)i;
        CHECK(ioport_claim(Port_Analog, Port_Input, &port, "sensor") != NULL);
    }
    describe_bank();
    CHECK(strstr(engine_output, "[AUX IO:0,0,0,2]" ASCII_EOL) != NULL);
    for(unsigned i = 0; i < 2; i++) {
        uint8_t port = (uint8_t)i;
        CHECK(ioport_claim(Port_Analog, Port_Output, &port, "actuator") != NULL);
    }
    describe_bank();
    CHECK(strstr(engine_output, "[AUX IO:") == NULL);
    CHECK(analog_output_calls == 0 && pwm_config_calls == 0);
    return EXIT_SUCCESS;
}
