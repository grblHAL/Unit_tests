#include <string.h>
#include "core_handlers.h"
#include "check.h"

int main(void)
{
    grbl.on_get_errors = errors_get_details;
    CHECK(errors_get_description(Status_BadNumberFormat) != NULL);
    CHECK(errors_get_description((status_code_t)250) == NULL);
    return EXIT_SUCCESS;
}
