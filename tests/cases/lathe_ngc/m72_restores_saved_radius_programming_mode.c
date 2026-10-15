#include "support/css_host.h"
#include "support/named_parameter_host.h"
int main(void)
{
    prepare_css_parser(true);
    CHECK(css_block("G8") == Status_OK);
    CHECK(css_block("M70") == Status_OK);
    CHECK(css_block("G7") == Status_OK);
    CHECK(css_block("M72") == Status_OK);
    NEAR(read_named_parameter("_lathe_diameter_mode"), 0);
    NEAR(read_named_parameter("_lathe_radius_mode"), 1);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
