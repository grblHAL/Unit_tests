#include "ppi_host.h"
int main(void)
{
    ppi_prepare(false, true);
    parser_block_t other = {.user_mcode = RGB_WriteLEDs};
    CHECK(grbl.user_mcode.check(RGB_WriteLEDs) == UserMCode_Normal);
    CHECK(grbl.user_mcode.validate(&other) == Status_GcodeValueOutOfRange);
    grbl.user_mcode.execute(STATE_IDLE, &other);
    grbl.on_report_options(true);
    grbl.on_report_options(false);
    CHECK(ppi_fallback_checks == 1 && ppi_fallback_validates == 1 && ppi_fallback_executes == 1 &&
          ppi_previous_reports == 2);
    return 0;
}
