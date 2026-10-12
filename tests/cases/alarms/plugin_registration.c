#include <string.h>
#include "core_handlers.h"
#include "check.h"

int main(void)
{
    grbl.on_get_alarms = alarms_get_details;
    static const alarm_detail_t a[] = {{(alarm_code_t)240, "First plugin"}};
    static const alarm_detail_t b[] = {{(alarm_code_t)241, "Second plugin"}};
    static alarm_details_t first = {.n_alarms = 1, .alarms = a};
    static alarm_details_t second = {.n_alarms = 1, .alarms = b};
    alarms_register(&first); alarms_register(&second);
    CHECK(alarms_get_details()->next == &first); CHECK(first.next == &second);
    CHECK(strcmp(alarms_get_description((alarm_code_t)240), "First plugin") == 0);
    CHECK(strcmp(alarms_get_description((alarm_code_t)241), "Second plugin") == 0);
    CHECK(alarms_get_description(Alarm_HardLimit) != NULL);
    return EXIT_SUCCESS;
}
