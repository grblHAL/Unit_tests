#include "support/scaling_parameter_report_host.h"
#include "support/css_host.h"

int main(void)
{
    prepare_css_parser(true);
    report_init_fns(); report_init();
    CHECK(css_block("G7G51X2Y3Z4") == Status_OK);
    CHECK(gc_state.modal.diameter_mode);
    check_scaling_parameter_report();
    return EXIT_SUCCESS;
}
