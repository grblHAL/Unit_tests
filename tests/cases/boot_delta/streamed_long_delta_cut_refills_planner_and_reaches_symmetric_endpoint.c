#include "support/boot_delta_stream_motion_host.h"
static float maximum_reported_feed;
static unsigned moving_reports;
static char moving_status[512];
static void capture_moving_status(const char *text)
{
    CHECK(strlen(moving_status) + strlen(text) < sizeof(moving_status));
    strcat(moving_status, text);
}
static void observe_delta_feed(sys_state_t state)
{
    boot_motion_foreground(state);
    if(state_get() == STATE_CYCLE && boot_motor_pulses[0]) {
        float feed = st_get_realtime_rate();
        CHECK(isfinite(feed) && feed >= 0 && feed <= 101);
        if(feed > maximum_reported_feed) maximum_reported_feed = feed;
        if(!moving_reports && feed > 95) {
            report_realtime_status(capture_moving_status, &hal.stream.report);
            const char *value = strstr(moving_status, "|FS:");
            if(!value) value = strstr(moving_status, "|F:");
            CHECK(value != NULL && strncmp(moving_status, "<Run", 4) == 0);
            float reported = strtof(strchr(value, ':') + 1, NULL);
            CHECK(fabsf(reported - feed) <= 1);
            moving_reports++;
        }
    }
}
int main(void)
{
    prepare_boot_delta_stream_motion("$10=8\nG91G1Z-10F100\n");
    boot_on_realtime = observe_delta_feed;
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    for(unsigned axis = 0; axis < 3; axis++) {
        CHECK(sys.position[axis] == 98);
        CHECK(boot_motor_position[axis] == 98);
        CHECK(boot_motor_pulses[axis] == 98);
    }
    CHECK(fabsf(gc_state.position[X_AXIS]) < .001f && fabsf(gc_state.position[Y_AXIS]) < .001f);
    /* Quantized joint counters allow a small Cartesian rounding difference. */
    CHECK(fabsf(gc_state.position[Z_AXIS] - (delta_zero_angle_height() - 10.0f)) < .03f);
    CHECK(boot_motion_full_planner_seen && boot_motion_before_ack);
    CHECK(moving_reports == 1 && maximum_reported_feed > 95);
    NEAR(st_get_realtime_rate(), 0);
    return EXIT_SUCCESS;
}
