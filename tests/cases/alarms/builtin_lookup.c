#include <string.h>
#include "core_handlers.h"
#include "check.h"

int main(void)
{
    grbl.on_get_alarms = alarms_get_details;
    CHECK(alarms_get_description(Alarm_HardLimit) != NULL);
    CHECK(alarms_get_description((alarm_code_t)250) == NULL);
    return EXIT_SUCCESS;
}
