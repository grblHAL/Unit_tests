#pragma once
#include "fatfs_host.h"
#include "networking/httpd.h"
#include "fs_handlers.h"
#include "grbl/fs_ram.h"
typedef struct
{
    const char *path, *filename, *action, *quiet, *uri, *content_type;
    char status[64];
    unsigned headers, released;
} files_request_t;
extern bool files_maintenance;
void files_prepare(http_request_t *request, files_request_t *parameters);
const char *files_action(http_request_t *request);
void files_response(char *buffer, size_t capacity);
void files_readback(const char *path, const void *expected, size_t size);
void files_upload(http_request_t *request, const char *name, const void *bytes, size_t size,
                  size_t chunk);
