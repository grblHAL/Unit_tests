#include "support/catalog_report_host.h"
#include "check.h"

int main(void)
{
    prepare_catalog_report();
    CHECK(report_alarm_details(false) == Status_OK);
    CHECK(strcmp(engine_output, "[ALARMCODE:1||first]" ASCII_EOL
                               "[ALARMCODE:2||]" ASCII_EOL
                               "[ALARMCODE:3||third]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
