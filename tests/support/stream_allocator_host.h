#pragma once
#include "support/stream_connection_host.h"
void *__real_malloc(size_t size);
void __real_free(void *ptr);
static void *stream_allocated_nodes[4];
static unsigned stream_node_frees;
void __wrap_free(void *ptr)
{
    for(unsigned i = 0; i < 4; i++) if(ptr && stream_allocated_nodes[i] == ptr) {
        stream_allocated_nodes[i] = NULL; stream_node_frees++; break;
    }
    __real_free(ptr);
}
static bool observe_stream_allocations;
static unsigned reject_stream_allocations, rejected_stream_allocations, stream_allocation_calls;
void *__wrap_malloc(size_t size)
{
    if(observe_stream_allocations) {
        stream_allocation_calls++;
        if(reject_stream_allocations) {
            reject_stream_allocations--; rejected_stream_allocations++;
            fprintf(stderr,"Injected auxiliary stream allocation failure\n");
            return NULL;
        }
    }
    void *result = __real_malloc(size);
    if(observe_stream_allocations && result) {
        CHECK(stream_allocation_calls <= 4);
        stream_allocated_nodes[stream_allocation_calls-1] = result;
    }
    return result;
}
