#include "support/corrupt_work_offset_host.h"
int main(void)
{
    prepare_corrupt_work_offset();
    check_failed_work_offset_preserves_pending_cut("G55G1X100F100");
    CHECK(canned_block("G1X3F100") == Status_OK);
    CHECK(canned_block("G55G1X4F100") == Status_OK);
    finish_work_offset_recovery(320);
    return EXIT_SUCCESS;
}
