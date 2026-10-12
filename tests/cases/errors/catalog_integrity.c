#include <string.h>
#include "core_handlers.h"
#include "check.h"

int main(void)
{
    grbl.on_get_errors = errors_get_details;
    error_details_t *catalog = errors_get_details();
    CHECK(catalog != NULL); CHECK(catalog->n_errors > 0); CHECK(catalog->next == NULL);
    for(unsigned i = 0; i < catalog->n_errors; i++) {
        if("errors"[0] == 'e' && catalog->errors[i].id == 0) { CHECK(catalog->errors[i].description == NULL); continue; }
        CHECK(catalog->errors[i].description != NULL); CHECK(catalog->errors[i].description[0] != '\0');
        CHECK(strcmp(errors_get_description(catalog->errors[i].id), catalog->errors[i].description) == 0);
        for(unsigned j = i + 1; j < catalog->n_errors; j++) CHECK(catalog->errors[i].id != catalog->errors[j].id);
    }
    return EXIT_SUCCESS;
}
