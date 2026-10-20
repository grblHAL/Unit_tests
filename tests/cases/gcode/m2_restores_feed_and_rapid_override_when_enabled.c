#include "support/program_end_storage_host.h"
int main(void)
{
    prepare_program_end(false);
    CHECK(store_setting(Setting_RestoreOverrides, "1") == Status_OK);
    plan_feed_override(125, 50);
    CHECK(sys.override.feed_rate == 125 && sys.override.rapid_rate == 50);
    CHECK(program_block("M2") == Status_OK);
    CHECK(sys.override.feed_rate == 100 && sys.override.rapid_rate == 100);
    return EXIT_SUCCESS;
}
