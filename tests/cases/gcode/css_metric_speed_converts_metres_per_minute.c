#include "support/css_host.h"
#include "check.h"

int main(void)
{
    prepare_css_parser(true);
    CHECK(css_block("G96S100") == Status_OK);
    CHECK(gc_spindle_get(0)->rpm_mode == SpindleSpeedMode_CSS);
    NEAR(spindle_get(0)->param->css.surface_speed, 100000);
    return EXIT_SUCCESS;
}
