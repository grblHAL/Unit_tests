#include "support/css_host.h"
#include "check.h"

int main(void)
{
    prepare_css_parser(true);
    CHECK(css_block("G96S100D2500") == Status_OK);
    CHECK(css_block("G97S3000") == Status_OK);
    CHECK(gc_spindle_get(0)->rpm_mode == SpindleSpeedMode_RPM);
    NEAR(gc_spindle_get(0)->rpm, 3000);
    return EXIT_SUCCESS;
}
