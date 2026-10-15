#pragma once
#include "support/boot_homing_motion_host.h"
static bool boot_motion_exit_queued, boot_motion_full_planner_seen, boot_motion_before_ack;
static unsigned boot_motion_service_calls, boot_motion_expected_acks;
static bool boot_motion_physical_nvs;
static unsigned boot_motion_ack_count(void)
{
    unsigned count = 0;
    const char *cursor = engine_output, *end;
    while((end = strchr(cursor, '\n'))) {
        size_t length = (size_t)(end - cursor);
        if(length && cursor[length - 1] == '\r') length--;
        if(length == 2 && cursor[0] == 'o' && cursor[1] == 'k') count++;
        cursor = end + 1;
    }
    return count;
}
static void boot_motion_foreground(sys_state_t state)
{
    CHECK(++boot_motion_service_calls < 200000);
    engine_ticks++;
    if(plan_check_full_buffer()) boot_motion_full_planner_seen = true;
    if(state == STATE_CYCLE || state == STATE_JOG || state == STATE_HOMING)
        stepper_driver_interrupt_handler();
    if(boot_motion_ack_count() < boot_motion_expected_acks)
        for(unsigned axis = 0; axis < N_AXIS; axis++)
            if(boot_motor_pulses[axis]) boot_motion_before_ack = true;
    if(!boot_motion_exit_queued && boot_wake_calls > 0 && sys.driver_started && boot_reads >= strlen(boot_program) &&
       state_get() == STATE_IDLE && plan_get_current_block() == NULL &&
       boot_motion_ack_count() >= boot_motion_expected_acks) {
        CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
        boot_motion_exit_queued = true;
    }
}
static void install_boot_motion_driver(void)
{
    install_boot_homing_driver();
    if(boot_motion_physical_nvs) hal.nvs.type = NVS_EEPROM;
    settings.homing.flags.enabled = settings.homing.flags.init_lock = false;
    settings.arc_tolerance = .002f; // Valid standard arc tolerance before settings reload.
    for(unsigned axis = 0; axis < N_AXIS; axis++) settings.axis[axis].max_travel = -200;
    settings_write_global();
    if(boot_restore_position)
        memcpy(boot_motor_position, boot_hardware_position, sizeof(boot_motor_position));
    grbl.on_execute_delay = boot_motion_foreground;
}
static inline void prepare_boot_stream_motion(const char *program)
{
    boot_program = program;
    for(const char *line = program; *line; line++)
        if(*line == '\n') boot_motion_expected_acks++;
    CHECK(boot_motion_expected_acks > 0);
    boot_homing_required = false;
    boot_during_init = install_boot_motion_driver;
    boot_on_realtime = boot_motion_foreground;
    boot_observe_fault_loop = true;
    boot_read_limit = 100000;
}
static inline void check_boot_motion_completion(void)
{
    if(!boot_motion_exit_queued || boot_wake_calls == 0) fprintf(stderr, "Boot motion exit=%u wakes=%u reads=%u services=%u output=%s\n",
        boot_motion_exit_queued, boot_wake_calls, boot_reads, boot_motion_service_calls, engine_output);
    CHECK(boot_motion_exit_queued && boot_wake_calls > 0);
    CHECK(boot_motion_ack_count() == boot_motion_expected_acks);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(plan_get_current_block() == NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
}
