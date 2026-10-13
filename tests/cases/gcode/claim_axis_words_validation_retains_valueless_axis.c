#include "support/engine_host.h"
#include <math.h>
#include "check.h"

static parser_block_t axis_block(void)
{
    parser_block_t block = {0};
    block.words.x = block.words.y = On;
    block.values.xyz[X_AXIS] = NAN;
    block.values.xyz[Y_AXIS] = 4;
    return block;
}

int main(void)
{
    parser_block_t block = axis_block();
    axes_signals_t claimed = gc_claim_axis_words(&block, (axes_signals_t){.mask = 1});
    CHECK(claimed.mask == 0);
    CHECK(block.words.x && block.words.y);

    block = axis_block();
    claimed = gc_claim_axis_words(&block, (axes_signals_t){.mask = 3});
    CHECK(claimed.mask == (1u << Y_AXIS));
    CHECK(block.words.x && !block.words.y);
    CHECK(isnan(block.values.xyz[X_AXIS]));

    block = axis_block();
    claimed = gc_claim_axis_words(&block, (axes_signals_t){.mask = 2});
    CHECK(claimed.mask == (1u << Y_AXIS));
    CHECK(block.words.x && !block.words.y);

    block = axis_block();
    claimed = gc_claim_axis_words(&block, (axes_signals_t){.mask = 0});
    CHECK(claimed.mask == 3);
    CHECK(!block.words.x && !block.words.y);
    return EXIT_SUCCESS;
}
