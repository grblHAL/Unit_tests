#include "support/named_parameter_host.h"
#include "support/malloc_failure_host.h"

int main(void)
{
    engine_parser_prepare();
    char kept[] = "_kept", pending[] = "_pending";
    CHECK(ngc_named_param_set(kept, 12.5f));
    fail_malloc = true;
    bool inserted = ngc_named_param_set(pending, 42);
    fail_malloc = false;
    CHECK(!inserted && failed_malloc_calls == 1);
    NEAR(read_named_parameter("_kept"), 12.5f);
    float value = 99;
    CHECK(!ngc_named_param_get(pending, &value));
    NEAR(value, 0);
    fail_malloc = true;
    bool updated = ngc_named_param_set(kept, 13.5f);
    fail_malloc = false;
    CHECK(updated && failed_malloc_calls == 1);
    NEAR(read_named_parameter("_kept"), 13.5f);
    CHECK(ngc_named_param_set(pending, 42));
    NEAR(read_named_parameter("_pending"), 42);
    NEAR(read_named_parameter("_kept"), 13.5f);
    CHECK(failed_malloc_calls == 1);
    return EXIT_SUCCESS;
}
