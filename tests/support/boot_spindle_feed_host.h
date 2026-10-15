#pragma once
#include "support/boot_stream_motion_host.h"
#include "support/named_parameter_host.h"
static spindle_state_t boot_feed_spindle_state;
static spindle_data_t boot_feed_feedback;
static unsigned boot_feed_rpm_reads, boot_feed_angle_reads;
static spindle_data_t *boot_feed_data(spindle_data_request_t request)
{
    if(request == SpindleData_RPM) boot_feed_rpm_reads++;
    if(request == SpindleData_AngularPosition) boot_feed_angle_reads++;
    return &boot_feed_feedback;
}
static void boot_feed_reset(void) { boot_feed_feedback.index_count = 0; boot_feed_feedback.angular_position = 0; }
static void boot_feed_output(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    CHECK(spindle->id == 0); boot_feed_spindle_state = state;
    boot_feed_feedback.rpm = state.on ? rpm : 0;
}
static spindle_state_t boot_feed_input(spindle_ptrs_t *spindle)
{ CHECK(spindle->id == 0); return boot_feed_spindle_state; }
static void install_boot_spindle_feed_driver(void)
{
    install_boot_motion_driver();
    static const spindle_ptrs_t driver = {.type = SpindleType_Basic, .ref_id = 1,
        .rpm_min = 10, .rpm_max = 12000,
        .cap = {.variable = true, .direction = true, .rpm_range_locked = true},
        .set_state = boot_feed_output, .get_state = boot_feed_input,
        .get_data = boot_feed_data, .reset_data = boot_feed_reset};
    hal.driver_cap.spindle_encoder = true;
    hal.spindle_data.get = boot_feed_data; hal.spindle_data.reset = boot_feed_reset;
    CHECK(spindle_register(&driver, "Encoder spindle") == 0);
    settings.spindle.ref_id = 1; settings.spindle.ppr = 100;
    settings.mode = Mode_Lathe;
    settings_write_global();
}
static inline void prepare_boot_spindle_feed(const char *program)
{
    prepare_boot_stream_motion(program);
    boot_during_init = install_boot_spindle_feed_driver;
}
