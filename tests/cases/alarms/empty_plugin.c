#include <string.h>
#include "core_handlers.h"
#include "check.h"

int main(void)
{
    grbl.on_get_alarms = alarms_get_details;
    static alarm_details_t empty = {.n_alarms = 0, .alarms = NULL};
    alarms_register(&empty);
    CHECK(alarms_get_description((alarm_code_t)240) == NULL);
    CHECK(alarms_get_description(Alarm_HardLimit) != NULL);
    return EXIT_SUCCESS;
}
