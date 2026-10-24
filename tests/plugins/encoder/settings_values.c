#include "encoder_host.h"
int main(void)
{
 encoder_prepare(1, false); encoder_load();
 CHECK(encoder_set(Setting_EncoderCPRBase, 800) == Status_OK && encoder_set(Setting_EncoderCPDBase, 8) == Status_OK);
 CHECK(encoder_set(Setting_EncoderDblClickWindowBase, 700) == Status_OK);
 CHECK(encoder_get(Setting_EncoderCPRBase) == 800 && encoder_get(Setting_EncoderCPDBase) == 8 && encoder_get(Setting_EncoderDblClickWindowBase) == 700);
 CHECK(encoder_configs[0].dbl_click_window == 700 && encoder_configs[0].vel_timeout == 0);
 CHECK(encoder_settings->normalize(Setting_EncoderCPRBase) == Setting_EncoderCPRBase); return 0;
}
