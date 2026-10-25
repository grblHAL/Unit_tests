#include "ppi_host.h"
int main(void)
{
    ppi_prepare(false, true);
    parser_block_t block = {.user_mcode = LaserPPI_Rate};
    CHECK(grbl.user_mcode.validate(&block) == Status_GcodeValueWordMissing);
    block.words.p = On;
    block.values.p = 254;
    CHECK(grbl.user_mcode.validate(&block) == Status_OK && block.user_mcode_sync && !block.words.p);
    block = (parser_block_t){.user_mcode = LaserPPI_Enable, .words.p = On, .values.p = 1};
    CHECK(grbl.user_mcode.validate(&block) == Status_OK && !block.user_mcode_sync);
    return 0;
}
