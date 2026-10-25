#include "encoder_host.h"
int main(void)
{
 encoder_prepare(1, false); encoder_load(); encoder_emit(0, 8, 400, (encoder_event_t){.position_changed = On});
 CHECK(encoder_command_count == 2 && encoder_commands[0] == CMD_OVERRIDE_FEED_FINE_PLUS && encoder_commands[1] == CMD_OVERRIDE_FEED_FINE_PLUS);
 encoder_emit(0, 4, 400, (encoder_event_t){.position_changed = On});
 encoder_emit(0, 4, 0, (encoder_event_t){.dbl_click = On});
 CHECK(encoder_command_count == 4 && encoder_commands[2] == CMD_OVERRIDE_FEED_FINE_MINUS && encoder_commands[3] == CMD_OVERRIDE_FEED_RESET);
 CHECK(encoder_resets == 2); return 0;
}
