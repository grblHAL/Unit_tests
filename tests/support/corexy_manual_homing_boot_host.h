#pragma once
#include "support/boot_host.h"

static void configure_manual_corexy_reference(settings_t *current)
{
    CHECK(current == &settings);
    /* Enable, single-axis commands, origin at zero, allow manual. */
    char options[] = "43";
    CHECK(settings_store_setting(Setting_HomingEnable, options) == Status_OK);
    for(unsigned slot = 0; slot < N_AXIS; slot++) {
        char empty[] = "0";
        CHECK(settings_store_setting((setting_id_t)(Setting_HomingCycle_1 + slot), empty) == Status_OK);
    }
    CHECK(settings.homing.flags.manual && settings.homing.flags.force_set_origin);
    CHECK(sys.homing.mask == 0);
}

static inline void prepare_manual_corexy_reference(const char *program)
{
    boot_during_setup = configure_manual_corexy_reference;
    boot_restore_position = true;
    boot_hardware_position[0] = 800;
    boot_hardware_position[1] = 0;
    boot_hardware_position[2] = 80;
    boot_program = program;
    /* boot_host rejects every pulse/wakeup: manual referencing must not move. */
}
