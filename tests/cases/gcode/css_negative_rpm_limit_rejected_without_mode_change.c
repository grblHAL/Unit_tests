#include "support/css_host.h"
#include "check.h"

int main(void)
{
    prepare_css_parser(true);
    CHECK(css_block("G96S100D-1") == Status_NegativeValue);
    CHECK(gc_spindle_get(0)->rpm_mode == SpindleSpeedMode_RPM);
    return EXIT_SUCCESS;
}
