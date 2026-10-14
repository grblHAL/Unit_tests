#include "support/modal_detail_report_host.h"

int main(void)
{
    prepare_report(); hal.coolant_cap.flood = true;
    modal_report_block("M8");
    CHECK(strstr(engine_output, " M8 ") != NULL && strstr(engine_output, " M9 ") == NULL);
    modal_report_block("M9");
    CHECK(strstr(engine_output, " M9 ") != NULL && strstr(engine_output, " M8 ") == NULL);
    return EXIT_SUCCESS;
}
