#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle_program();
    CHECK(spindle_enable(1) == 1);
    CHECK(spindle_program_block("M3S5000") == Status_OK);
    CHECK(spindle_program_block("M3S7000$1") == Status_OK);
    status_code_t status = spindle_program_block("M5$-1");
    fprintf(stderr, "broadcast stop status=%u, expected=0\n", (unsigned)status);
    CHECK(status == Status_OK);
    CHECK(!actual_spindle_states[0].on && !actual_spindle_states[1].on);
    CHECK(actual_spindle_rpm[0] == 0 && actual_spindle_rpm[1] == 0);
    return EXIT_SUCCESS;
}
