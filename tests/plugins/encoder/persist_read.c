#include "encoder_host.h"
int main(void)
{
 encoder_prepare(1, false); FILE *file = fopen("encoder.nvs", "rb"); CHECK(file);
 CHECK(fread(memory, 1, hal.nvs.size_max, file) == hal.nvs.size_max && fclose(file) == 0); encoder_load();
 CHECK(encoder_get(Setting_EncoderModeBase) == 3 && encoder_configs[0].dbl_click_window == 700);
 encoder_emit(0, 8, 400, (encoder_event_t){.position_changed = On});
 CHECK(encoder_command_count == 1 && encoder_commands[0] == CMD_OVERRIDE_SPINDLE_FINE_PLUS);
 CHECK(remove("encoder.nvs") == 0); return 0;
}
