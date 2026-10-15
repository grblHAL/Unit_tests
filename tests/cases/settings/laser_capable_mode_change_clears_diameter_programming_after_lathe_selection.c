#include "support/spindle_caps_host.h"
#include "support/settings_host.h"
#include "state_machine.h"
int main(void)
{
    /* Register/configure the PWM spindle before parser initialization. */
    prepare_spindle_caps(true);
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++)
        settings_write_coord_data((coord_system_id_t)i, &coordinates);
    gc_init(false);
    CHECK(plan_reset());
    state_set(STATE_CHECK_MODE);
    grbl.on_settings_changed = changed_settings;
    CHECK(store_setting(Setting_Mode, "2") == Status_OK);
    CHECK(settings.mode == Mode_Lathe);
    char diameter[] = "G7";
    CHECK(gc_execute_block(diameter) == Status_OK);
    CHECK(gc_state.modal.diameter_mode);
    CHECK(store_setting(Setting_Mode, "1") == Status_OK);
    CHECK(settings.mode == Mode_Laser && !gc_state.modal.diameter_mode);
    const setting_detail_t *mode = setting_get_details(Setting_Mode, NULL);
    CHECK(mode && setting_get_int_value(mode, 0) == Mode_Laser);
    CHECK(change_callbacks == 2);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
