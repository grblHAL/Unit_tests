#include "support/boot_host.h"
#include "support/ioports_settings_host.h"

static unsigned servo_configurations;
static bool servo_configure(xbar_t *pin, xbar_cfg_ptr_t data, bool persistent)
{
    CHECK(pin == &digital_pins[Port_Output][0] && !persistent);
    CHECK(data.pwm_config != NULL);
    NEAR(data.pwm_config->freq_hz, 50);
    CHECK(data.pwm_config->servo_mode);
    servo_configurations++;
    return true;
}
static void install_mixed_output_driver(void)
{
    for(unsigned i = 0; i < 2; i++) {
        digital_pins[Port_Input][i].mode.input = true;
        digital_pins[Port_Input][i].mode.pull_mode = PullMode_Up;
        digital_pins[Port_Input][i].config = configure_input;
        digital_pins[Port_Output][i].mode.output = true;
        digital_pins[Port_Output][i].config = configure_output;
    }
    digital_pins[Port_Output][0].mode.servo_pwm = true;
    digital_pins[Port_Output][0].cap.servo_pwm = true;
    digital_pins[Port_Output][0].cap.pwm = true;
    digital_pins[Port_Output][0].config = servo_configure;
    register_ioports();
    settings.ioport.invert_out.mask = 3;
    settings.ioport.od_enable_out.mask = 3;
    settings_write_global();
}

static void configure_loaded_driver_pins(settings_t *current)
{
    CHECK(current == &settings && sys.ioinit_pending);
    grbl.on_settings_changed(current, (settings_changed_flags_t){0});
}

int main(void)
{
    boot_during_init = install_mixed_output_driver;
    boot_during_setup = configure_loaded_driver_pins;
    CHECK(grbl_enter() == 0);
    CHECK(servo_configurations == 0 && output_config_calls[0] == 0);
    CHECK(output_config_calls[1] > 0);
    CHECK(captured_output[1].inverted && captured_output[1].open_drain);
    CHECK(digital_pins[Port_Output][0].mode.servo_pwm);
    pwm_config_t servo = {.freq_hz = 50, .min = 0, .max = 180,
        .min_value = 5, .max_value = 10, .servo_mode = true};
    uint8_t owned = 0;
    CHECK(ioport_claim(Port_Digital, Port_Output, &owned, "Servo") != NULL);
    CHECK(ioport_digital_pwm_config(owned, &servo));
    CHECK(servo_configurations == 1 && output_config_calls[0] == 0);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(strstr(engine_output, "[GC:") != NULL);
    return EXIT_SUCCESS;
}
