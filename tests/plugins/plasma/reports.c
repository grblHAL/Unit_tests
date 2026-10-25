#include "plasma_host.h"
int main(void)
{
    plasma_prepare(3, true);
    plasma_load();
    grbl.on_report_options(true);
    grbl.on_report_options(false);
    CHECK(plasma_prior_reports == 2 && strstr(plasma_output, "PLASMA (Off)") && !plasma_steps &&
          !plasma_warnings);
    return 0;
}
