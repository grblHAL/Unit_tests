#include "bltouch_host.h"
int main(void)
{
    load_bltouch();
    parser_block_t block = {0};
    block.user_mcode = Probe_Deploy;
    block.words.d = On;
    block.values.d = 0.5f;
    status_code_t status = grbl.user_mcode.validate(&block);
    CHECK(outputs == 1 && angle == 90);
    CHECK(status == Status_BadNumberFormat);
    return 0;
}
