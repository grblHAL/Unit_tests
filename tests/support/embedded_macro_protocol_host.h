#pragma once
#include "support/ram_macro_protocol_host.h"
#include "fs_embedded.h"
static const embedded_file_t named_macro_asset = {
    .name = "fixture.macro", .size = sizeof(NAMED_MACRO_BODY) - 1, .data = NAMED_MACRO_BODY
};
#ifdef INNER_MACRO_BODY
static const embedded_file_t inner_macro_asset = {
    .name = "inner.macro", .size = sizeof(INNER_MACRO_BODY) - 1, .data = INNER_MACRO_BODY
};
#endif
static const embedded_file_t *named_macro_assets[] = {&named_macro_asset,
#ifdef INNER_MACRO_BODY
    &inner_macro_asset,
#endif
    NULL};
static void register_named_macro_assets(void) { fs_embedded_mount(named_macro_assets); }
static inline void run_named_macro_protocol(const char *program)
{
    ram_prepare_assets = register_named_macro_assets;
    run_ram_root_protocol(program);
}
