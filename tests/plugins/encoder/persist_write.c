#include "encoder_host.h"
int main(void)
{
 encoder_prepare(1, false); encoder_load(); CHECK(encoder_set(Setting_EncoderModeBase, 3) == Status_OK);
 CHECK(encoder_set(Setting_EncoderCPRBase, 800) == Status_OK && encoder_set(Setting_EncoderDblClickWindowBase, 700) == Status_OK);
 encoder_settings->save(); FILE *file = fopen("encoder.nvs", "wb"); CHECK(file);
 CHECK(fwrite(memory, 1, hal.nvs.size_max, file) == hal.nvs.size_max && fclose(file) == 0); return 0;
}
