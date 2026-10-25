#include "encoder_host.h"
int main(void)
{
 encoder_prepare(1, false); encoder_load(); encoder_emit(0, 0, 0, (encoder_event_t){.click = On});
 grbl.on_realtime_report(hal.stream.write, (report_tracking_flags_t){.encoder = On}); CHECK(strstr(encoder_output, "|Enc:2|Previous:1"));
 encoder_emit(0, -4, 400, (encoder_event_t){.position_changed = On}); CHECK(encoder_commands[0] == CMD_OVERRIDE_RAPID_MEDIUM);
 encoder_emit(0, -4, 0, (encoder_event_t){.click = On}); encoder_emit(0, 0, 400, (encoder_event_t){.position_changed = On});
 encoder_emit(0, 0, 0, (encoder_event_t){.dbl_click = On});
 CHECK(encoder_command_count == 3 && encoder_commands[1] == CMD_OVERRIDE_SPINDLE_FINE_PLUS && encoder_commands[2] == CMD_OVERRIDE_SPINDLE_RESET);
 CHECK(encoder_reports == 2); encoder_run_tasks(); return 0;
}
