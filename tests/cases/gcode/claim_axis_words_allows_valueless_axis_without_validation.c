#include "support/engine_host.h"
#include <math.h>
#include "check.h"

int main(void)
{
    parser_block_t block = {0};
    block.words.x = On;
    block.values.xyz[X_AXIS] = NAN;
    axes_signals_t claimed = gc_claim_axis_words(&block, (axes_signals_t){0});
    CHECK(claimed.mask == (1u << X_AXIS));
    CHECK(!block.words.x);
    CHECK(isnan(block.values.xyz[X_AXIS]));
    return EXIT_SUCCESS;
}
