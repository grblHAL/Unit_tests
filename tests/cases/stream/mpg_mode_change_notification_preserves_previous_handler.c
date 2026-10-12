#include "support/mpg_stream_host.h"
#include "check.h"
static unsigned previous_mode_calls;
static void previous_mode_handler(void) { previous_mode_calls++; }

int main(void)
{
    prepare_mpg_stream();
    grbl.on_gcode_mode_changed = previous_mode_handler;
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    grbl.on_gcode_mode_changed();
    CHECK(previous_mode_calls == 1);
    CHECK(strstr(pendant_output, "[GC:G0 G54 G17 G21 G90") != NULL);
    return EXIT_SUCCESS;
}
