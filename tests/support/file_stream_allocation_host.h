#pragma once
#include "support/nested_ram_stream_host.h"
#include "fs_embedded.h"
#include "support/tracked_malloc_host.h"
static const embedded_file_t allocation_parent = {.name = "parent", .size = 8, .data = {'G','9','0','\n','G','9','1','\n'}};
static const embedded_file_t allocation_child = {.name = "child", .size = 5, .data = {'F','1','0','0','\n'}};
static const embedded_file_t *allocation_files[] = {&allocation_parent, &allocation_child, NULL};
static inline void prepare_file_heap(void)
{
    prepare_ram_stream_environment();
    fs_embedded_mount(allocation_files);
}
static inline void reject_file_open(unsigned allocation, const char *path)
{
    allocation_heap_reject = allocation;
    observe_allocation_heap = true;
    vfs_file_t *file = stream_redirect_read(path, NULL, NULL);
    observe_allocation_heap = false; /* Never inject into reporting/coverage shutdown. */
    CHECK(file == NULL && allocation_heap_failures == 1 && allocation_heap_calls == allocation);
    CHECK(allocation_heap_frees == allocation - 1);
    for(unsigned i = 0; i < 4; i++) CHECK(allocation_heap_allocations[i] == NULL);
}
