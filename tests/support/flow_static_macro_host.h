#pragma once
#include "support/flow_file_host.h"
#include "report.h"
static ngc_string_id_t static_macro_label;
static void (*static_macro_on_open)(void);
static char static_macro_path[128] = "/fixture.macro";
static vfs_file_t *open_static_macro(const char *name, const char *mode)
{
    if(strcmp(name, static_macro_path) || strcmp(mode, "r"))
        return NULL;
    file_position = 0;
    if(static_macro_on_open) static_macro_on_open();
    return &fixture_file;
}
static int stat_static_macro(const char *name, vfs_stat_t *st)
{
    if(strcmp(name, static_macro_path))
        return -1;
    memset(st, 0, sizeof(*st));
    st->st_size = strlen(file_text);
    return 0;
}
static bool static_macro_connected(void) { return true; }
static inline void prepare_static_macro_named(const char *macro_name)
{
    CHECK(strlen(macro_name) + sizeof("/.macro") <= sizeof(static_macro_path));
    strcpy(static_macro_path, "/");
    strcat(static_macro_path, macro_name);
    strcat(static_macro_path, ".macro");
    prepare_file_stream("G21\n");
    static const vfs_t backend = {.fopen = open_static_macro, .fclose = close_file,
        .fread = read_file, .ftell = tell_file, .fseek = seek_file, .fstat = stat_static_macro};
    CHECK(vfs_mount(NULL, "/", &backend, (vfs_st_mode_t){.directory = true}));
    hal.stream.is_connected = static_macro_connected;
    report_init_fns();
    report_init();
    char name[128];
    strcpy(name, macro_name);
    static_macro_label = ngc_string_param_set_name(name);
    CHECK(static_macro_label > NGC_MAX_PARAM_ID);
    flow_skip = false;
}

static inline void prepare_static_macro(void)
{
    prepare_static_macro_named("fixture");
}
