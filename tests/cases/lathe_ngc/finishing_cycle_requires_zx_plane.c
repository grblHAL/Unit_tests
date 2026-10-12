#include "support/css_host.h"
#include "check.h"

int main(void)
{
    prepare_css_parser(true);
    CHECK(css_block("G70X10Z20Q7F100") == Status_GcodeIllegalPlane);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
