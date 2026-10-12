#include "support/css_host.h"
#include "check.h"
int main(void)
{
    prepare_css_parser(true);
    CHECK(gc_spindle_get(0)->rpm_mode == SpindleSpeedMode_RPM);
    CHECK(css_block("G96S-1") == Status_NegativeValue);
    fprintf(stderr, "RPM mode after rejected CSS block=%u, expected=%u\n", (unsigned)gc_spindle_get(0)->rpm_mode, (unsigned)SpindleSpeedMode_RPM);
    CHECK(gc_spindle_get(0)->rpm_mode == SpindleSpeedMode_RPM);
    return EXIT_SUCCESS;
}
