#include "support/secondary_pwm_settings_host.h"

int main(void)
{
    engine_prepare();
    hal.nvs.type = NVS_EEPROM;
    analog_pins[Port_Output][0].config = configure_pwm;
    analog_pins[Port_Output][0].cap.pwm = true;
    static io_ports_data_t analog_ports = {.out.n_ports = 1};
    static io_ports_data_t digital_ports = {.out.n_ports = 1};
    io_analog_t analog = {.ports = &analog_ports, .get_pin_info = analog_pin_info,
        .set_pin_description = analog_description, .analog_out = analog_output};
    io_digital_t digital = {.ports = &digital_ports, .get_pin_info = pin_info,
        .set_pin_description = pin_description, .digital_out = pin_output};
    CHECK(ioports_add_analog(&analog) && ioports_add_digital(&digital));
    secondary_pwm_settings = spindle1_settings_add(true);
    CHECK(secondary_pwm_settings != NULL);
    spindle1_settings_register((spindle_cap_t){.variable = true}, NULL);
    CHECK(setting_get_details(Setting_SpindleInvertMask1, &secondary_pwm_owner) != NULL);
    CHECK(secondary_pwm_owner != NULL);
    secondary_pwm_owner->restore();
    secondary_pwm_owner->load();
    CHECK(secondary_pwm_settings->port_on == 0 && secondary_pwm_settings->port_pwm == 0);
    CHECK(secondary_pwm_settings->port_dir == IOPORT_UNASSIGNED);
    const setting_detail_t *on = setting_get_details(Setting_Spindle_OnPort, NULL);
    const setting_detail_t *direction = setting_get_details(Setting_Spindle_DirPort, NULL);
    const setting_detail_t *pwm = setting_get_details(Setting_Spindle_PWMPort, NULL);
    CHECK(on != NULL && direction != NULL && pwm != NULL);
    NEAR(setting_get_float_value(on, 0), 0);
    NEAR(setting_get_float_value(pwm, 0), 0);
    NEAR(setting_get_float_value(direction, 0), -1);
    CHECK(output_calls == 0 && analog_output_calls == 0);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
