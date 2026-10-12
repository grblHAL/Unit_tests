#include "support/css_host.h"
#include "check.h"

int main(void)
{
    prepare_css_parser(true);
    CHECK(css_block("G96S100D2500") == Status_OK);
    NEAR(spindle_get(0)->param->css.max_rpm, 2500);
    return EXIT_SUCCESS;
}
