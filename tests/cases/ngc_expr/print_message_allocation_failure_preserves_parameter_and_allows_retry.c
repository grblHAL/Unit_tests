#include "support/engine_host.h"
#include "ngc_expr.h"
#include "ngc_params.h"
#include "check.h"
#include <string.h>
static bool fail_message;
static unsigned failures;
void *__real_malloc(size_t size);
void *__wrap_malloc(size_t size)
{
    if(fail_message && size == sizeof("part=7.500")) {
        fail_message = false;
        failures++;
        return NULL;
    }
    return __real_malloc(size);
}
int main(void)
{
    engine_parser_prepare();
    CHECK(ngc_param_set(1, 7.5f));
    char failed[] = "PRINT,part=#1";
    fail_message = true;
    CHECK(ngc_process_comment(failed) == NULL);
    CHECK(failures == 1 && !fail_message && failed[6] == 0);
    float value;
    CHECK(ngc_param_get(1, &value));
    NEAR(value, 7.5f);
    char retry[] = "PRINT,part=#1";
    char *message = ngc_process_comment(retry);
    CHECK(message && strcmp(message, "part=7.500") == 0);
    free(message);
    CHECK(failures == 1 && retry[6] == 0);
    return EXIT_SUCCESS;
}
