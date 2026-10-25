#include "atci_host.h"
int main(void)
{
    atci_start();
    unsigned before = chains;
    grbl.on_report_options(true);
    grbl.on_report_options(false);
    CHECK(chains == before + 3);
    parser_block_t block = {0};
    block.user_mcode = (user_mcode_t)999;
    CHECK(grbl.user_mcode.check(block.user_mcode) == UserMCode_Normal);
    CHECK(grbl.user_mcode.validate(&block) == Status_SettingDisabled);
    grbl.user_mcode.execute(STATE_IDLE, &block);
    CHECK(chains == before + 6);
    return 0;
}
