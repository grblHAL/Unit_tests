#include "table_host.h"
#include <string.h>
grbl_hal_t hal;
grbl_t grbl;
settings_t settings;
system_t sys;
bool file_exists = true, fail_read, fail_write;
char table_text[4096] = "T1 P1 X1 Y-2 Z3 D6 ;mill|rough\nT2 P7 Z-4 D3 ;drill\n";
unsigned opens, closes, selections, changes, mount_calls, options, reports;
typedef struct
{
    vfs_file_t file;
    size_t position;
    bool writing;
} table_file_t;
static vfs_file_t *open_file(const char *path, const char *mode)
{
    CHECK(strcmp(path, "/tooltable.tbl") == 0);
    bool writing = strcmp(mode, "w") == 0;
    CHECK(writing || strcmp(mode, "r") == 0);
    if ((writing && fail_write) || (!writing && (!file_exists || fail_read)))
        return NULL;
    table_file_t *file = calloc(1, sizeof(*file));
    CHECK(file);
    if (writing)
    {
        table_text[0] = 0;
        file_exists = true;
    }
    file->writing = writing;
    file->file.size = strlen(table_text);
    opens++;
    return &file->file;
}
static void close_file(vfs_file_t *file)
{
    closes++;
    free(file);
}
static size_t read_file(void *data, size_t size, size_t count, vfs_file_t *file)
{
    table_file_t *f = (table_file_t *)file;
    CHECK(!f->writing && size > 0 && f->position <= strlen(table_text));
    size_t available = (strlen(table_text) - f->position) / size;
    if (count > available)
        count = available;
    memcpy(data, table_text + f->position, size * count);
    f->position += size * count;
    return count;
}
static size_t write_file(const void *data, size_t size, size_t count, vfs_file_t *file)
{
    table_file_t *f = (table_file_t *)file;
    CHECK(f->writing && size > 0 && count < sizeof(table_text) / size);
    CHECK(f->position + size * count < sizeof(table_text));
    memcpy(table_text + f->position, data, size * count);
    f->position += size * count;
    table_text[f->position] = 0;
    file->size = f->position;
    return count;
}
static int seek_file(vfs_file_t *file, size_t position)
{
    CHECK(position <= strlen(table_text));
    ((table_file_t *)file)->position = position;
    return 0;
}
static void selected(tool_data_t *tool, bool next)
{
    CHECK(tool);
    (void)next;
    selections++;
}
static void changed(tool_data_t *tool)
{
    CHECK(tool);
    changes++;
}
static void mounted(const char *path, const vfs_t *fs, vfs_st_mode_t mode)
{
    CHECK(strcmp(path, "/linuxcnc") == 0 && fs && mode.directory);
    mount_calls++;
}
static void option_report(bool newopt)
{
    (void)newopt;
    options++;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(strcmp(name, "Tool table") == 0 && strcmp(version, "0.04") == 0);
    reports++;
}
void system_register_commands(sys_commands_t *commands)
{
    CHECK(commands->n_commands == 1 && strcmp(commands->commands[0].command, "TTLOAD") == 0);
}
sys_state_t state_get(void) { return STATE_IDLE; }
bool protocol_execute_realtime(void)
{
    CHECK(false);
    return false;
}
bool protocol_exec_rt_system(void)
{
    CHECK(false);
    return false;
}
bool state_door_reopened(void)
{
    CHECK(false);
    return false;
}
bool stream_await_tx_clear(const io_stream_t *stream)
{
    (void)stream;
    CHECK(false);
    return false;
}
void start_table(void)
{
    void tooltable_init(void);
    static const vfs_t fs = {.fs_name = "table-fixture",
                             .fopen = open_file,
                             .fclose = close_file,
                             .fread = read_file,
                             .fwrite = write_file,
                             .fseek = seek_file};
    hal.tool.select = selected;
    grbl.on_tool_changed = changed;
    grbl.on_report_options = option_report;
    vfs.on_mount = mounted;
    tooltable_init();
    CHECK(vfs_mount(NULL, "/linuxcnc", &fs, (vfs_st_mode_t){.directory = On}));
    CHECK(mount_calls == 1 && opens == closes);
}
