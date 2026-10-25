#include "overdrive_host.h"
int main(void)
{
    ovd_prepare();
    CHECK(grbl.user_mcode.check((user_mcode_t)999) == UserMCode_Unsupported);
    parser_block_t block = {.user_mcode = (user_mcode_t)999};
    CHECK(grbl.user_mcode.validate(&block) == Status_Unhandled);
    grbl.user_mcode.execute(STATE_IDLE, &block);
    grbl.on_report_options(true);
    grbl.on_report_options(false);
    CHECK(ovd_checks == 1 && ovd_validates == 1 && ovd_executes == 1);
    CHECK(ovd_reports == 2 && ovd_plugins == 1);
    return 0;
}
