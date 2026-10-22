#pragma once
#include "support/motion_program_host.h"
#include "ngc_params.h"
static float live_cut_feed = 100;
static unsigned live_feed_reads;
static float read_cut_feed(void) { live_feed_reads++; return live_cut_feed; }
static inline void register_cut_feed(void)
{
    // A public virtual provider models plugin ownership, not plasma material parsing.
    CHECK(ngc_virtual_ro_param_add("_hal[plasmac.cut-feed-rate]", read_cut_feed));
}
static inline status_code_t cut_feed_block(const char *text)
{
    char block[128];
    CHECK(strlen(text) < sizeof(block));
    strcpy(block, text);
    return gc_execute_block(block);
}
