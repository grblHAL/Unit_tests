#pragma once
#include "fs_embedded.h"
#include "support/tracked_malloc_host.h"
#include <string.h>
static const embedded_file_t heap_first = {.name = "first", .size = 1, .data = {'a'}};
static const embedded_file_t *heap_files[] = {&heap_first, NULL};
static inline void begin_embedded_heap_failure(unsigned allocation)
{
    allocation_heap_reject = allocation;
    observe_allocation_heap = true;
}
static inline void end_embedded_heap_failure(unsigned allocation)
{
    observe_allocation_heap = false;
    CHECK(allocation_heap_calls == allocation && allocation_heap_failures == 1);
    CHECK(allocation_heap_frees == allocation - 1);
    for(unsigned i = 0; i < 4; i++) CHECK(allocation_heap_allocations[i] == NULL);
}
static inline void check_embedded_directory(bool appended)
{
    vfs_dir_t *dir = vfs_opendir("/embedded");
    CHECK(dir != NULL);
    vfs_dirent_t *entry = vfs_readdir(dir);
    CHECK(entry != NULL && strcmp(entry->name, "first") == 0);
    if(appended) {
        entry = vfs_readdir(dir);
        CHECK(entry != NULL && strcmp(entry->name, "second") == 0);
    }
    CHECK(vfs_readdir(dir) == NULL);
    vfs_closedir(dir);
}
