#include "encoder_host.h"
int main(void)
{
 encoder_prepare(1, false); encoder_storage_ok = false; on_report_options_ptr before = grbl.on_report_options;
 CHECK(!encoder_init() && encoder_settings == NULL && encoder_claims == 0 && grbl.on_report_options == before); return 0;
}
