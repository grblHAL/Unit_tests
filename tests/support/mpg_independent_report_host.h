#pragma once
#include "support/mpg_stream_host.h"
static void request_primary_status(void)
{
    CHECK(protocol_enqueue_realtime_command(CMD_STATUS_REPORT));
    CHECK(protocol_exec_rt_system());
}
static void request_pendant_status(void)
{
    CHECK(stream_mpg_check_enable(CMD_STATUS_REPORT));
    engine_execute_tasks(STATE_IDLE);
}
static inline void check_independent_pending_reports(bool primary_first, bool wco)
{
    prepare_mpg_stream();
    settings.status_report.overrides = !wco;
    settings.status_report.work_coord_offset = wco;
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    request_primary_status();
    request_pendant_status();
    primary_output[0] = pendant_output[0] = '\0';
    if(wco) {
        char offset[] = "G10L2P1X12";
        CHECK(gc_execute_block(offset) == Status_OK);
        report_add_realtime(Report_WCO);
    } else {
        CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_FEED_COARSE_PLUS));
        CHECK(protocol_exec_rt_system());
        CHECK(sys.override.feed_rate == 110);
    }
    const char *expected = wco ? "|WCO:12.000,0.000,0.000" : "|Ov:110,100,100";
    if(primary_first) {
        request_primary_status();
        CHECK(strstr(primary_output, expected) != NULL);
        /* Primary replies broadcast to connected streams; the pendant still has
           its own pending report, consumed only by its directed request. */
        CHECK(strstr(pendant_output, expected) != NULL);
        pendant_output[0] = '\0';
        primary_output[0] = '\0';
        request_pendant_status();
        CHECK(strstr(pendant_output, expected) != NULL);
        CHECK(primary_output[0] == '\0');
    } else {
        request_pendant_status();
        CHECK(strstr(pendant_output, expected) != NULL);
        CHECK(primary_output[0] == '\0');
        pendant_output[0] = '\0';
        request_primary_status();
        CHECK(strstr(primary_output, expected) != NULL);
        CHECK(strstr(pendant_output, expected) != NULL);
    }
    CHECK(state_get() == STATE_IDLE && !sys.mpg_mode);
    CHECK(hal.stream.read == primary_input);
}
