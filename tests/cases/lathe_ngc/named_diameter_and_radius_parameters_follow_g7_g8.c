#include "support/css_host.h"
#include "support/named_parameter_host.h"

int main(void)
{
    prepare_css_parser(true);
    CHECK(css_block("G7") == Status_OK);
    NEAR(read_named_parameter("_lathe_diameter_mode"), 1);
    NEAR(read_named_parameter("_lathe_radius_mode"), 0);
    CHECK(css_block("G8") == Status_OK);
    NEAR(read_named_parameter("_lathe_diameter_mode"), 0);
    NEAR(read_named_parameter("_lathe_radius_mode"), 1);
    return EXIT_SUCCESS;
}
