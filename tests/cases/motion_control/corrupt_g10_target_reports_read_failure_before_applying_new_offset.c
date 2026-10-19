#include "support/corrupt_work_offset_host.h"
int main(void)
{
    prepare_corrupt_work_offset();
    check_failed_work_offset_preserves_pending_cut("G10L2P2X5");
    CHECK(canned_block("G10L2P2X5") == Status_OK);
    CHECK(canned_block("G1X3F100") == Status_OK);
    CHECK(canned_block("G55G1X1F100") == Status_OK);
    finish_work_offset_recovery(480);
    return EXIT_SUCCESS;
}
