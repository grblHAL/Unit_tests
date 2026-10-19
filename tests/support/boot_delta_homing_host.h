#pragma once
#include "support/boot_delta_stream_motion_host.h"
#include "kinematics/interface.h"
static bool boot_delta_cuboid_home, boot_delta_home_finished;
static unsigned boot_delta_home_events, boot_delta_homing_pulses[N_AXIS];
static void observe_boot_delta_home(axes_signals_t cycle, bool success)
{
    CHECK(cycle.mask == AXES_BITMASK && success);
    boot_delta_home_events++;
    memcpy(boot_delta_homing_pulses, boot_motor_pulses, sizeof(boot_delta_homing_pulses));
}
static void boot_delta_home_foreground(sys_state_t state)
{
    boot_homing_foreground(state);
    if(!boot_delta_home_finished && boot_delta_home_events == 1 &&
       boot_reads == strlen(boot_program) && boot_motion_ack_count() == 2 &&
       state == STATE_IDLE && plan_get_current_block() == NULL) {
        coord_data_t cartesian;
        mpos_t steps;
        memcpy(&steps, sys.position, sizeof(steps));
        kinematics.transform_steps_to_cartesian(&cartesian, &steps);
        if(!boot_delta_cuboid_home || fabsf(cartesian.z - sys.home_position[Z_AXIS]) < .15f) {
            boot_delta_home_finished = true;
            CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
        }
    }
}
static void install_delta_homing_driver(void)
{
    hal.nvs.type = NVS_EEPROM;
    install_boot_homing_driver();
    settings.homing.pulloff = 1;
    for(unsigned axis = 0; axis < 3; axis++) {
        settings.axis[axis].steps_per_mm = 1000;
        settings.axis[axis].max_travel = -2;
        settings.axis[axis].max_rate = 10;
        settings.axis[axis].homing_seek_rate = 10;
        settings.axis[axis].homing_feed_rate = 2;
    }
    settings_write_global();
    grbl.on_homing_completed = observe_boot_delta_home;
    grbl.on_execute_delay = boot_delta_home_foreground;
}
static void configure_delta_homing(settings_t *current)
{
    CHECK(current == &settings);
    char flags[] = "1";
    if(boot_delta_cuboid_home)
        CHECK(settings_store_setting(Setting_Kinematics7, flags) == Status_OK);
}
static inline void prepare_boot_delta_homing(bool cuboid)
{
    boot_delta_cuboid_home = cuboid;
    boot_homing_required = true;
    boot_observe_fault_loop = true;
    boot_read_limit = 100000;
    boot_during_init = install_delta_homing_driver;
    boot_during_setup = configure_delta_homing;
    boot_on_realtime = boot_delta_home_foreground;
    boot_program = "$H\n$G\n";
}
