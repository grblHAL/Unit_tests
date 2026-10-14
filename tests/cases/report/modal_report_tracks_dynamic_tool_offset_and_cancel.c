#include "support/modal_detail_report_host.h"

int main(void)
{
    prepare_report();
    modal_report_block("G43.1Z5");
    CHECK(strstr(engine_output, " G43.1 ") != NULL && strstr(engine_output, " G49 ") == NULL);
    modal_report_block("G49");
    CHECK(strstr(engine_output, " G49 ") != NULL && strstr(engine_output, " G43.1 ") == NULL);
    return EXIT_SUCCESS;
}
