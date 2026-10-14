#include "support/mpg_observer_host.h"
int main(void)
{
    prepare_mpg_stream();
    grbl.on_gcode_mode_changed = previous_modes;
    CHECK(stream_mpg_register(&pendant_device,false,NULL));
    CHECK(stream_mpg_enable(true));
    pendant_output[0] = 0;
    grbl.on_gcode_mode_changed();
    CHECK(previous_calls == 1 && pendant_output[0] == 0);
    return EXIT_SUCCESS;
}
