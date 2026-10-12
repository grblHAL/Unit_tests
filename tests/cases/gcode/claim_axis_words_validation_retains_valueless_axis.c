#include "support/engine_host.h"
#include <math.h>
#include "check.h"

int main(void)
{
    parser_block_t block = {0};
    block.words.x = block.words.y = On;
    block.values.xyz[X_AXIS] = NAN;
    block.values.xyz[Y_AXIS] = 4;
    axes_signals_t claimed = gc_claim_axis_words(&block, (axes_signals_t){.mask = 1});
    CHECK(claimed.mask == (1u << Y_AXIS));
    CHECK(block.words.x);
    CHECK(!block.words.y);
    CHECK(isnan(block.values.xyz[X_AXIS]));
    return EXIT_SUCCESS;
}
