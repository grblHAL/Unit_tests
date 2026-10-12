#include "support/report_host.h"
#include "stream.h"
#include "protocol.h"
#include "check.h"
static unsigned line_calls;
static io_stream_properties_t captured_property;
static serial_linestate_t captured_line;
static void capture_usb_line(io_stream_properties_t *stream, serial_linestate_t state)
{
    line_calls++;
    captured_property = *stream;
    captured_line = state;
}

int main(void)
{
    prepare_report();
    hal.stream.on_linestate_changed = capture_usb_line;
    stream_usb_linestate_changed(2, (serial_linestate_t){.rts = true});
    CHECK(line_calls == 1);
    CHECK(captured_property.type == StreamType_Serial);
    CHECK(captured_property.instance == 2);
    CHECK(captured_property.flags.is_usb);
    CHECK(captured_line.rts && !captured_line.dtr);
    CHECK(engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
