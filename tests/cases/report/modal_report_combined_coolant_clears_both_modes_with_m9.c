#include "support/modal_detail_report_host.h"

int main(void)
{
    prepare_report(); hal.coolant_cap.flood = hal.coolant_cap.mist = true;
    modal_report_block("M7"); modal_report_block("M8");
    CHECK(strstr(engine_output, " M7 ") != NULL && strstr(engine_output, " M8 ") != NULL);
    modal_report_block("M9");
    CHECK(strstr(engine_output, " M9 ") != NULL);
    CHECK(strstr(engine_output, " M7 ") == NULL && strstr(engine_output, " M8 ") == NULL);
    return EXIT_SUCCESS;
}
