#pragma once
#include "support/ram_macro_protocol_host.h"
#include "fs_embedded.h"
// Named files are scanned through matching ENDSUB before body execution.
static const embedded_file_t named_macro_asset = {
    .name = "fixture.macro",
    .size = sizeof("O<fixture>SUB\n" NAMED_MACRO_BODY "O<fixture>ENDSUB\n") - 1,
    .data = "O<fixture>SUB\n" NAMED_MACRO_BODY "O<fixture>ENDSUB\n"
};
#ifdef INNER_MACRO_BODY
static const embedded_file_t inner_macro_asset = {
    .name = "inner.macro",
    .size = sizeof("O<inner>SUB\n" INNER_MACRO_BODY "O<inner>ENDSUB\n") - 1,
    .data = "O<inner>SUB\n" INNER_MACRO_BODY "O<inner>ENDSUB\n"
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
