#include "support/modal_detail_report_host.h"

int main(void)
{
    prepare_report();
    modal_report_block("G51X2Y3Z1");
    CHECK(strstr(engine_output, " G51:XY ") != NULL && strstr(engine_output, " G50 ") == NULL);
    modal_report_block("G50");
    CHECK(strstr(engine_output, " G50 ") != NULL && strstr(engine_output, " G51:") == NULL);
    return EXIT_SUCCESS;
}
