#include "support/motion_program_host.h"
void *__real_malloc(size_t size);
void __real_free(void *pointer);
static bool observe_allocations;
static void *allocations[16];
static size_t allocation_sizes[16];
static unsigned allocation_count;
void *__wrap_malloc(size_t size)
{
    void *pointer = __real_malloc(size);
    if(observe_allocations && pointer) {
        CHECK(allocation_count < 16);
        allocations[allocation_count] = pointer;
        allocation_sizes[allocation_count++] = size;
    }
    return pointer;
}
void __wrap_free(void *pointer)
{
    for(unsigned i = 0; i < allocation_count; i++)
        if(pointer && allocations[i] == pointer) {
            allocations[i] = NULL;
            break;
        }
    __real_free(pointer);
}
int main(void)
{
    prepare_motion_program();
    observe_allocations = true;
    queue_motion_program("G1X10F100(MSG,Future move)");
    CHECK(plan_reset());
    observe_allocations = false;
    CHECK(plan_get_current_block() == NULL && allocation_count > 0);
    size_t outstanding_bytes = 0;
    for(unsigned i = 0; i < allocation_count; i++)
        if(allocations[i]) outstanding_bytes += allocation_sizes[i];
    fprintf(stderr, "Message bytes left after parser/planner cleanup: %zu\n", outstanding_bytes);
    CHECK(outstanding_bytes == 0);
    return EXIT_SUCCESS;
}
