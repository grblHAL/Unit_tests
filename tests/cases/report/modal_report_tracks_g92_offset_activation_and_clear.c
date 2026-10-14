#include "support/modal_detail_report_host.h"

int main(void)
{
    prepare_report();
    modal_report_block("G92X3"); CHECK(strstr(engine_output, " G92 ") != NULL);
    modal_report_block("G92.1"); CHECK(strstr(engine_output, " G92 ") == NULL);
    return EXIT_SUCCESS;
}
