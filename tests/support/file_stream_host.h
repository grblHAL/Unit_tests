#pragma once
#include "support/engine_host.h"
#include "stream_file.h"
#include "stream.h"
#include "check.h"
#include <string.h>
static const char *file_text;
static size_t file_position;
static unsigned file_closes;
static vfs_file_t fixture_file;
static vfs_file_t *open_file(const char *name, const char *mode)
{
    if(strcmp(name, "/program") || strcmp(mode, "r")) return NULL;
    file_position = 0;
    return &fixture_file;
}
static void close_file(vfs_file_t *file) { CHECK(file == &fixture_file); file_closes++; }
static size_t read_file(void *buffer, size_t size, size_t count, vfs_file_t *file)
{
    CHECK(file == &fixture_file);
    size_t available = strlen(file_text) - file_position;
    size_t bytes = size * count < available ? size * count : available;
    memcpy(buffer, file_text + file_position, bytes);
    file_position += bytes;
    return bytes;
}
static size_t tell_file(vfs_file_t *file) { CHECK(file == &fixture_file); return file_position; }
static int seek_file(vfs_file_t *file, size_t position)
{
    CHECK(file == &fixture_file);
    if(position > strlen(file_text)) return -1;
    file_position = position;
    return 0;
}
static inline void prepare_file_stream(const char *text)
{
    static const vfs_t backend = {.fopen = open_file, .fclose = close_file,
        .fread = read_file, .ftell = tell_file, .fseek = seek_file};
    engine_parser_prepare();
    file_text = text;
    hal.stream.read = stream_get_null;
    CHECK(vfs_mount(NULL, "/fixture", &backend, (vfs_st_mode_t){.directory = true, .hidden = true}));
}
