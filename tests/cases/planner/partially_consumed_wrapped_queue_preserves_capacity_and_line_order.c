#include "support/engine_host.h"
#include "check.h"
static void append_line(unsigned number)
{
    float target[N_AXIS] = {(float)number};
    plan_line_data_t data = {.feed_rate = 100, .line_number = number};
    CHECK(!plan_check_full_buffer());
    CHECK(plan_buffer_line(target, &data));
}
int main(void)
{
    engine_prepare();
    char blocks[] = "35";
    CHECK(settings_store_setting(Setting_PlannerBlocks, blocks) == Status_OK);
    CHECK(plan_reset());
    for(unsigned i = 1; i <= 35; i++) append_line(i);
    CHECK(plan_check_full_buffer());
    for(unsigned i = 1; i <= 20; i++) {
        CHECK(plan_get_current_block()->line_number == i);
        plan_discard_current_block();
        CHECK(plan_get_block_buffer_available() == i);
    }
    for(unsigned i = 36; i <= 53; i++) {
        append_line(i);
        CHECK(plan_get_block_buffer_available() == 55 - i);
    }
    for(unsigned i = 21; i <= 53; i++) {
        CHECK(plan_get_current_block()->line_number == i);
        plan_discard_current_block();
        CHECK(plan_get_block_buffer_available() == i - 18);
    }
    CHECK(plan_get_current_block() == NULL);
    for(unsigned i = 54; i <= 88; i++) append_line(i);
    CHECK(plan_check_full_buffer() && plan_get_block_buffer_available() == 0);
    CHECK(plan_reset() && plan_get_block_buffer_available() == 35);
    return EXIT_SUCCESS;
}
