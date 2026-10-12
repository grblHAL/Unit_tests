#include <string.h>
#include "core_handlers.h"
#include "check.h"

int main(void)
{
    grbl.on_get_errors = errors_get_details;
    static const status_detail_t a[] = {{(status_code_t)240, "First plugin"}};
    static const status_detail_t b[] = {{(status_code_t)241, "Second plugin"}};
    static error_details_t first = {.n_errors = 1, .errors = a};
    static error_details_t second = {.n_errors = 1, .errors = b};
    errors_register(&first); errors_register(&second);
    CHECK(errors_get_details()->next == &first); CHECK(first.next == &second);
    CHECK(strcmp(errors_get_description((status_code_t)240), "First plugin") == 0);
    CHECK(strcmp(errors_get_description((status_code_t)241), "Second plugin") == 0);
    CHECK(errors_get_description(Status_BadNumberFormat) != NULL);
    return EXIT_SUCCESS;
}
