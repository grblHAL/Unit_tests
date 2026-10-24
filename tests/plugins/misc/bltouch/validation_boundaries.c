#include "bltouch_host.h"
int main(void)
{
    load_bltouch();
    const float invalid[] = {-1, 2, 0.5f};
    for (unsigned i = 0; i < 3; i++)
    {
        status_code_t expected = i == 2 ? Status_BadNumberFormat : Status_GcodeValueOutOfRange;
        parser_block_t block = {0};
        block.user_mcode = Probe_Deploy;
        block.words.s = On;
        block.values.s = invalid[i];
        CHECK(dispatch_bltouch(&block) == expected);
        block = (parser_block_t){0};
        block.user_mcode = Probe_Deploy;
        block.words.r = On;
        block.values.r = invalid[i];
        CHECK(dispatch_bltouch(&block) == expected);
        block = (parser_block_t){0};
        block.user_mcode = Probe_Stow;
        block.words.r = On;
        block.values.r = invalid[i];
        CHECK(dispatch_bltouch(&block) == expected);
    }
    CHECK(outputs == 1 && angle == 90);
    parser_block_t block = {0};
    block.user_mcode = Probe_Deploy;
    block.words.r = On;
    CHECK(dispatch_bltouch(&block) == Status_OK && angle == 10);
    block = (parser_block_t){0};
    block.user_mcode = Probe_Stow;
    block.words.r = On;
    block.values.r = 1;
    CHECK(dispatch_bltouch(&block) == Status_OK && angle == 90);
    return 0;
}
