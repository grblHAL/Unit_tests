#include "support/css_host.h"
#include "check.h"
#include <float.h>

int main(void)
{
    prepare_css_parser(true);
    CHECK(css_block("G20G96S100") == Status_OK);
    CHECK(gc_state.modal.units_imperial);
    CHECK(fabsf(spindle_get(0)->param->css.surface_speed - 30480.0f) <= 30480.0f * FLT_EPSILON);
    return EXIT_SUCCESS;
}
