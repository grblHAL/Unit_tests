#include "cluster_host.h"
system_t sys;
grbl_hal_t hal;
grbl_t grbl;
parser_state_t gc_state;
bool cluster_file;
unsigned cluster_statuses, cluster_previous_streams, cluster_previous_resets,
    cluster_previous_reports, cluster_handler_inits;
status_code_t cluster_last_status;
char cluster_output[1024];
static const char *source;
static size_t source_pos;
static int32_t source_read(void)
{
    return source[source_pos] ? (unsigned char)source[source_pos++] : SERIAL_NO_DATA;
}
void cluster_source(const char *data)
{
    CHECK(!source || !source[source_pos]);
    source = data;
    source_pos = 0;
}
static void output(const char *text)
{
    CHECK(strlen(cluster_output) + strlen(text) < sizeof(cluster_output));
    strcat(cluster_output, text);
}
static status_code_t status(status_code_t value)
{
    cluster_statuses++;
    cluster_last_status = value;
    return value;
}
static void stream_changed(void) { cluster_previous_streams++; }
static void reset(void) { cluster_previous_resets++; }
static void report_options(bool newopt)
{
    (void)newopt;
    cluster_previous_reports++;
}
static void init_handlers(void)
{
    cluster_handler_inits++;
    grbl.report.status_message = status;
}
bool stream_is_file(void) { return cluster_file; }
void system_raise_alarm(alarm_code_t alarm)
{
    (void)alarm;
    CHECK(false);
}
bool protocol_execute_realtime(void)
{
    CHECK(false);
    return false;
}
bool protocol_exec_rt_system(void)
{
    CHECK(false);
    return false;
}
bool state_door_reopened(void)
{
    CHECK(false);
    return false;
}
void cluster_prepare(bool file, const char *data)
{
    cluster_file = file;
    cluster_source(data);
    hal.stream.read = source_read;
    hal.stream.write = output;
    grbl.on_stream_changed = stream_changed;
    grbl.on_reset = reset;
    grbl.on_report_options = report_options;
    grbl.on_report_handlers_init = init_handlers;
    lb_clusters_init();
    grbl.on_report_handlers_init();
}
void cluster_change(bool file, const char *data)
{
    cluster_file = file;
    cluster_source(data);
    hal.stream.read = source_read;
    grbl.on_stream_changed();
}
void cluster_drain(char *out, size_t size)
{
    size_t used = 0;
    unsigned idle = 0;
    for (unsigned count = 0; count < 4096; count++)
    {
        int32_t c = hal.stream.read();
        if (c == SERIAL_NO_DATA)
        {
            if (++idle == 32)
            {
                out[used] = 0;
                return;
            }
            continue;
        }
        CHECK(c >= 0 && c <= 255 && used + 1 < size);
        idle = 0;
        out[used++] = (char)c;
        if (c == '\n' || c == '\r')
            grbl.report.status_message(Status_OK);
    }
    CHECK(false);
}
