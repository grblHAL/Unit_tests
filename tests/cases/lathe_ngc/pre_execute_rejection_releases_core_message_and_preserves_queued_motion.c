#include "support/pre_execute_host.h"
#include "support/tracked_malloc_host.h"
int main(void)
{
    prepare_pre_execute();
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    pre_execute_result = Status_GcodeInvalidTarget;
    observe_allocation_heap = true;
    status_code_t status = pre_execute_block("G20G91G1X2F2(MSG,Rejected move)");
    observe_allocation_heap = false;
    CHECK(status == Status_GcodeInvalidTarget && pre_execute_calls == 2);
    CHECK(plan_get_current_block() == first && allocation_heap_calls == 1);
    CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
    NEAR(gc_state.position[X_AXIS], 1);
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    CHECK(sys.position[X_AXIS] == 80);
    unsigned core_frees = allocation_heap_frees;
    // Reclaim probe-observed orphans only after recording CORE ownership behavior.
    for(unsigned i = 0; i < allocation_heap_calls; i++)
        if(allocation_heap_allocations[i]) free(allocation_heap_allocations[i]);
    CHECK(core_frees == 1);
    return EXIT_SUCCESS;
}
