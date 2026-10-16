#include "support/planner_allocation_host.h"
int main(void)
{
    configure_planner_blocks(35);
    planner_heap_limit = 0;
    CHECK(!plan_reset());
    CHECK(planner_rejected_allocations > 0);
    planner_heap_limit = (size_t)-1;
    CHECK(plan_reset());
    CHECK(plan_get_buffer_size() == 35);
    check_planner_capacity_is_usable();
    return EXIT_SUCCESS;
}
