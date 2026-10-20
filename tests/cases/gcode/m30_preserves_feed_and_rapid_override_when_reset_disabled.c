#include "support/program_end_storage_host.h"
int main(void)
{
    prepare_program_end(false);
    CHECK(store_setting(Setting_RestoreOverrides, "0") == Status_OK);
    plan_feed_override(125, 50);
    CHECK(program_block("M30") == Status_OK);
    CHECK(sys.override.feed_rate == 125 && sys.override.rapid_rate == 50);
    return EXIT_SUCCESS;
}
