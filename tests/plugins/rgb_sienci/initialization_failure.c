#include "rgb_host.h"
int main(void)
{
    rgb_prepare();
    hal.rgb0.out = NULL;
    status_light_init();
    CHECK(pending == 1);
    rgb_run_next();
    CHECK(warnings == 1);
    parser_block_t block = {0};
    block.user_mcode = (user_mcode_t)999;
    CHECK(grbl.user_mcode.validate(&block) == Status_SettingDisabled);
    CHECK(writes[0] == 0);
    return 0;
}
