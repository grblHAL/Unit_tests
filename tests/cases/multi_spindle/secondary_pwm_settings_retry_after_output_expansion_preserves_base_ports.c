#include "support/secondary_pwm_settings_host.h"

int main(void)
{
    prepare_ioports();
    hal.nvs.type = NVS_EEPROM;
    uint32_t original_storage = hal.nvs.driver_area.size;
    CHECK(ioports_available(Port_Digital, Port_Output) == 2);
    CHECK(ioports_available(Port_Analog, Port_Output) == 0);
    CHECK(spindle1_settings_add(true) == NULL);
    CHECK(hal.nvs.driver_area.address == 0 && hal.nvs.driver_area.size == original_storage);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 2);
    ioport_digital_out(0, true);
    CHECK(output_calls == 1 && physical_output == 0 && output_value);

    analog_pins[Port_Output][0].config = configure_pwm;
    analog_pins[Port_Output][0].cap.pwm = true;
    static io_ports_data_t expansion_ports = {.out.n_ports = 1};
    io_analog_t expansion = {.ports = &expansion_ports, .get_pin_info = analog_pin_info,
        .set_pin_description = analog_description, .analog_out = analog_output};
    CHECK(ioports_add_analog(&expansion));
    secondary_pwm_settings = spindle1_settings_add(true);
    CHECK(secondary_pwm_settings != NULL && hal.nvs.driver_area.size > original_storage);
    grbl.on_settings_changed = primary_pwm_changed;
    spindle1_settings_register((spindle_cap_t){.variable = true, .direction = true, .pwm_invert = true}, secondary_pwm_changed);
    CHECK(setting_get_details(Setting_SpindleInvertMask1, &secondary_pwm_owner) != NULL);
    CHECK(secondary_pwm_owner != NULL);
    secondary_pwm_owner->restore();
    secondary_pwm_owner->load();
    CHECK(secondary_pwm_settings->port_pwm == 0 && secondary_pwm_settings->port_on == 1);
    CHECK(secondary_pwm_settings->port_dir == 0);
    CHECK(secondary_pwm_store(Setting_RpmMax1, "6000") == Status_OK);
    secondary_pwm_owner->load();
    NEAR(secondary_pwm_settings->cfg.rpm_max, 6000);
    CHECK(secondary_pwm_changes == 1 && primary_pwm_changes == 0);
    CHECK(output_calls == 1 && analog_output_calls == 0);
    CHECK(ioports_available(Port_Digital, Port_Output) == 2);
    CHECK(ioports_available(Port_Analog, Port_Output) == 1);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
