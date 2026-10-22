#include "support/pre_execute_host.h"
#include "support/tracked_malloc_host.h"
int main(void)
{
    prepare_pre_execute();
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    const char *rejected[] = {
        "G999(MSG,Unsupported command)",
        "G1X2F-1(MSG,Negative feed)",
        "G1X2F100Q1(MSG,Unused word)"
    };
    const status_code_t expected[] = {Status_GcodeUnsupportedCommand, Status_NegativeValue, Status_GcodeUnusedWords};
    unsigned released = 0;
    for(unsigned i = 0; i < sizeof(rejected) / sizeof(*rejected); i++) {
        allocation_heap_calls = allocation_heap_frees = 0;
        observe_allocation_heap = true;
        status_code_t status = pre_execute_block(rejected[i]);
        observe_allocation_heap = false;
        CHECK(status == expected[i] && allocation_heap_calls == 1);
        CHECK(plan_get_current_block() == first);
        NEAR(gc_state.position[X_AXIS], 1);
        released += allocation_heap_frees;
        // Reclaim observed orphans after recording parser ownership behavior.
        for(unsigned j = 0; j < allocation_heap_calls; j++)
            if(allocation_heap_allocations[j]) free(allocation_heap_allocations[j]);
    }
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    CHECK(sys.position[X_AXIS] == 80);
    fprintf(stderr, "Parser released %u of 3 rejected messages\n", released);
    CHECK(released == 3);
    return EXIT_SUCCESS;
}
