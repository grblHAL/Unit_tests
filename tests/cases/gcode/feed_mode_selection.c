#include <string.h>
#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); char inverse[] = "G93"; CHECK(gc_execute_block(inverse) == Status_OK);
    CHECK(gc_state.modal.feed_mode == FeedMode_InverseTime); char normal[] = "G94"; CHECK(gc_execute_block(normal) == Status_OK);
    CHECK(gc_state.modal.feed_mode == FeedMode_UnitsPerMin);
    return EXIT_SUCCESS;
}
