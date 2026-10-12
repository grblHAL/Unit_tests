#include "support/engine_host.h"
#include <math.h>
#include "check.h"

int main(void)
{
    parser_block_t block = {0};
    block.words.x = block.words.z = block.words.f = block.words.p = On;
    block.values.xyz[X_AXIS] = 12;
    block.values.xyz[Z_AXIS] = -3;
    axes_signals_t claimed = gc_claim_axis_words(&block, (axes_signals_t){0});
    CHECK(claimed.mask == ((1u << X_AXIS) | (1u << Z_AXIS)));
    CHECK(!block.words.x && !block.words.z);
    CHECK(block.words.f && block.words.p);
    NEAR(block.values.xyz[X_AXIS], 12);
    NEAR(block.values.xyz[Z_AXIS], -3);
    return EXIT_SUCCESS;
}
