#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare(); CHECK(plan_reset());
    CHECK(plan_get_buffer_size() == 16); CHECK(plan_get_block_buffer_available() == 16);
    CHECK(plan_get_current_block() == NULL); CHECK(plan_get_recent_block() == NULL); CHECK(!plan_check_full_buffer());
    plan_discard_current_block(); CHECK(plan_get_block_buffer_available() == 16);
    return EXIT_SUCCESS;
}
