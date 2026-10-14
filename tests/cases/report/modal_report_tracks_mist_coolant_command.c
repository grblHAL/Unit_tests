#include "support/modal_detail_report_host.h"

int main(void)
{
    prepare_report(); hal.coolant_cap.mist = true;
    modal_report_block("M7");
    CHECK(strstr(engine_output, " M7 ") != NULL);
    CHECK(strstr(engine_output, " M8 ") == NULL && strstr(engine_output, " M9 ") == NULL);
    return EXIT_SUCCESS;
}
