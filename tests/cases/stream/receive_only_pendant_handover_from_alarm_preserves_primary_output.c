#include "support/mpg_stream_host.h"

int main(void)
{
    prepare_mpg_stream();
    system_raise_alarm(Alarm_HomingRequired);
    CHECK(state_get() == STATE_ALARM && sys.alarm == Alarm_HomingRequired);
    CHECK(stream_mpg_register(&pendant_device, true, stream_mpg_check_enable));
    CHECK(!stream_is_busy(false));
    CHECK(stream_mpg_enable(true));
    CHECK(sys.mpg_mode && hal.stream.state.is_mpg);
    CHECK(primary_rx_disabled && !pendant_rx_disabled);
    CHECK(hal.stream.read == pendant_input && hal.stream.write == primary_write);
    primary_output[0] = pendant_output[0] = '\0';
    hal.stream.write("pendant active");
    CHECK(strcmp(primary_output, "pendant active") == 0 && pendant_output[0] == '\0');
    CHECK(stream_mpg_enable(false));
    CHECK(!sys.mpg_mode && !hal.stream.state.is_mpg && !primary_rx_disabled);
    CHECK(hal.stream.read == primary_input && hal.stream.write == primary_write);
    CHECK(pendant_rt == stream_mpg_check_enable);
    CHECK(state_get() == STATE_ALARM && sys.alarm == Alarm_HomingRequired);
    primary_output[0] = '\0';
    hal.stream.write("primary restored");
    CHECK(strcmp(primary_output, "primary restored") == 0 && pendant_output[0] == '\0');
    return EXIT_SUCCESS;
}
