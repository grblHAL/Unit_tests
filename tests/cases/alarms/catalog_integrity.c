#include <string.h>
#include "core_handlers.h"
#include "check.h"

int main(void)
{
    grbl.on_get_alarms = alarms_get_details;
    alarm_details_t *catalog = alarms_get_details();
    CHECK(catalog != NULL); CHECK(catalog->n_alarms > 0); CHECK(catalog->next == NULL);
    for(unsigned i = 0; i < catalog->n_alarms; i++) {
        CHECK(catalog->alarms[i].description != NULL); CHECK(catalog->alarms[i].description[0] != '\0');
        CHECK(strcmp(alarms_get_description(catalog->alarms[i].id), catalog->alarms[i].description) == 0);
        for(unsigned j = i + 1; j < catalog->n_alarms; j++) CHECK(catalog->alarms[i].id != catalog->alarms[j].id);
    }
    return EXIT_SUCCESS;
}
