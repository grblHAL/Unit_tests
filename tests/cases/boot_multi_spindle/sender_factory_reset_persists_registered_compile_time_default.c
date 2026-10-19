#include "support/boot_spindle_setup_host.h"
#include "nvs_buffer.h"
static bool saw_saved_secondary;
static void register_factory_spindles(void)
{
    for(unsigned i = 0; i < 2; i++) {
        setup_spindles[i] = (spindle_ptrs_t){.type = SpindleType_Basic,
            .ref_id = i ? 20 : DEFAULT_SPINDLE, .rpm_min = 1000, .rpm_max = 12000,
            .cap = {.direction = true, .rpm_range_locked = true},
            .config = configure_setup_spindle, .set_state = output_setup_spindle,
            .get_state = state_setup_spindle};
        CHECK(spindle_register(&setup_spindles[i], i ? "secondary" : "factory default") == (spindle_id_t)i);
    }
}
static void observe_secondary_before_reset(void)
{
    if(boot_reads == 0) {
        CHECK(spindle_get(0)->id == 1 && settings.spindle.ref_id == 20);
        saw_saved_secondary = true;
    }
}
int main(void)
{
    boot_spindle_reference = 20;
    boot_during_init = register_factory_spindles;
    boot_before_read = observe_secondary_before_reset;
    boot_program = "$RST=$\n";
    CHECK(grbl_enter() == 0);
    CHECK(saw_saved_secondary && strstr(engine_output, "error:") == NULL);
    CHECK(settings.spindle.ref_id == DEFAULT_SPINDLE);
    const setting_detail_t *default_spindle = setting_get_details(Setting_SpindleType, NULL);
    CHECK(default_spindle != NULL && default_spindle->flags.reboot_required);
    settings_t saved;
    CHECK(nvs_buffer_get_physical()->memcpy_from_nvs((uint8_t *)&saved, NVS_ADDR_GLOBAL,
        sizeof(saved), true) == NVS_TransferResult_OK);
    CHECK(saved.spindle.ref_id == DEFAULT_SPINDLE);
    CHECK(!setup_spindle_states[0].on && !setup_spindle_states[1].on);
    CHECK(sys.driver_started && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
