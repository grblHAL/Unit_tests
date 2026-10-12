#include <string.h>
#include "core_handlers.h"
#include "check.h"

int main(void)
{
    grbl.on_get_errors = errors_get_details;
    static error_details_t empty = {.n_errors = 0, .errors = NULL};
    errors_register(&empty);
    CHECK(errors_get_description((status_code_t)240) == NULL);
    CHECK(errors_get_description(Status_BadNumberFormat) != NULL);
    return EXIT_SUCCESS;
}
