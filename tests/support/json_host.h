#pragma once
#include "support/engine_host.h"
#include "vfs.h"
#include "stream_json.h"
#include "check.h"
#include <string.h>
static char json_output[1024];
static size_t json_output_length;
static size_t json_write(const void *buffer, size_t size, size_t count, vfs_file_t *file)
{
    (void)file;
    size_t length = json_output_length, bytes = size * count;
    CHECK(length + bytes < sizeof(json_output));
    memcpy(json_output + length, buffer, bytes);
    json_output_length += bytes;
    json_output[json_output_length] = '\0';
    return bytes;
}
static inline vfs_file_t *json_file(void)
{
    static const vfs_t backend = {.fwrite = json_write};
    static vfs_file_t file = {.fs = &backend};
    return &file;
}
