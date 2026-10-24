#include "encoder_host.h"
int main(void)
{
 encoder_prepare(1, false); encoder_load(); CHECK(encoders_get_count() == 1 && encoder_claims == 1 && encoder_resets == 1 && encoder_configures == 1);
 CHECK(encoder_get(Setting_EncoderModeBase) == 0 && encoder_get(Setting_EncoderCPRBase) == 400 && encoder_get(Setting_EncoderCPDBase) == 4);
 CHECK(encoder_configs[0].dbl_click_window == 500 && encoder_configs[0].vel_timeout == 0);
 grbl.on_report_options(false); CHECK(strcmp(encoder_output, "ENCODER") == 0 && encoder_previous_reports == 1); return 0;
}
