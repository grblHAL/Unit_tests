#pragma once
#include "support/flow_file_host.h"
#include "report.h"
static ngc_string_id_t static_macro_label;
static vfs_file_t *open_static_macro(const char *name, const char *mode)
{
    if(strcmp(name, "/fixture.macro") || strcmp(mode, "r"))
        return NULL;
    file_position = 0;
    return &fixture_file;
}
static int stat_static_macro(const char *name, vfs_stat_t *st)
{
    if(strcmp(name, "/fixture.macro"))
        return -1;
    memset(st, 0, sizeof(*st));
    st->st_size = strlen(file_text);
    return 0;
}
static bool static_macro_connected(void) { return true; }
static inline void prepare_static_macro(void)
{
    prepare_file_stream("G21\n");
    static const vfs_t backend = {.fopen = open_static_macro, .fclose = close_file,
        .fread = read_file, .ftell = tell_file, .fseek = seek_file, .fstat = stat_static_macro};
    CHECK(vfs_mount(NULL, "/", &backend, (vfs_st_mode_t){.directory = true}));
    hal.stream.is_connected = static_macro_connected;
    report_init_fns();
    report_init();
    char name[] = "fixture";
    static_macro_label = ngc_string_param_set_name(name);
    CHECK(static_macro_label > NGC_MAX_PARAM_ID);
    flow_skip = false;
}
