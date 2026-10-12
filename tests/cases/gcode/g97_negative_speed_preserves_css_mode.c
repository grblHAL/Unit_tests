#include "support/css_host.h"
#include "check.h"
int main(void)
{
    prepare_css_parser(true);
    CHECK(css_block("G96S100") == Status_OK);
    CHECK(gc_spindle_get(0)->rpm_mode == SpindleSpeedMode_CSS);
    CHECK(css_block("G97S-1") == Status_NegativeValue);
    fprintf(stderr, "mode after rejected G97=%u, expected=%u\n", (unsigned)gc_spindle_get(0)->rpm_mode, (unsigned)SpindleSpeedMode_CSS);
    CHECK(gc_spindle_get(0)->rpm_mode == SpindleSpeedMode_CSS);
    return EXIT_SUCCESS;
}
