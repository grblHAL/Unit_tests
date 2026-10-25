#include "encoder_host.h"
int main(void)
{
 encoder_prepare(1, false); encoder_load(); sys.override.rapid_rate = RAPID_OVERRIDE_EXTRA_LOW;
 encoder_emit(0, 0, 0, (encoder_event_t){.click = On}); encoder_emit(0, 4, 400, (encoder_event_t){.position_changed = On});
 CHECK(encoder_command_count == 1); fprintf(stderr, "rapid command=%u\n", encoder_commands[0]); CHECK(encoder_commands[0] == CMD_OVERRIDE_RAPID_LOW); return 0;
}
