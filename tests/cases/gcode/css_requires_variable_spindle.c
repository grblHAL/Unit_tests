#include "support/css_host.h"
#include "check.h"

int main(void)
{
    prepare_css_parser(false);
    CHECK(css_block("G96S100") == Status_GcodeUnsupportedCommand);
    return EXIT_SUCCESS;
}
