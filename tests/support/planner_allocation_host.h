#pragma once
#include "support/engine_host.h"
#include "check.h"
void *__real_malloc(size_t size);
/* Model the largest contiguous allocation available, not total controller RAM. */
static size_t planner_heap_limit = (size_t)-1;
static unsigned planner_rejected_allocations;
void *__wrap_malloc(size_t size)
{
    if(size > planner_heap_limit) {
        planner_rejected_allocations++;
        return NULL;
    }
    return __real_malloc(size);
}
static inline void configure_planner_blocks(unsigned blocks)
{
    engine_prepare();
    char value[16];
    snprintf(value, sizeof(value), "%u", blocks);
    CHECK(settings_store_setting(Setting_PlannerBlocks, value) == Status_OK);
}
static inline void check_planner_capacity_is_usable(void)
{
    unsigned capacity = plan_get_buffer_size();
    CHECK(capacity >= 30 && plan_get_block_buffer_available() == capacity);
    plan_line_data_t data = {.feed_rate = 100};
    float target[N_AXIS] = {0};
    for(unsigned i = 0; i < capacity; i++) {
        CHECK(!plan_check_full_buffer());
        target[X_AXIS] = (float)(i + 1);
        CHECK(plan_buffer_line(target, &data));
    }
    CHECK(plan_check_full_buffer() && plan_get_block_buffer_available() == 0);
    CHECK(plan_reset());
    CHECK(plan_get_current_block() == NULL);
    CHECK(plan_get_block_buffer_available() == capacity);
}
static inline void check_bounded_planner_fallback(unsigned requested, unsigned budget)
{
    configure_planner_blocks(requested);
    planner_heap_limit = (budget + 1) * sizeof(plan_block_t);
    CHECK(plan_reset());
    CHECK(planner_rejected_allocations > 0);
    unsigned capacity = plan_get_buffer_size();
    CHECK(capacity < requested && capacity <= budget);
    CHECK(settings.planner_buffer_blocks == requested);
    check_planner_capacity_is_usable();
}
