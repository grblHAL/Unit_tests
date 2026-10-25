#pragma once
#include "multipartparser.h"
#include "check.h"
#include <string.h>
#include <stdbool.h>
typedef struct
{
    char fields[160], values[256];
    uint8_t bytes[512];
    size_t field_length, value_length, length;
    bool headers_done, ended;
} upload_part_t;
typedef struct
{
    multipartparser parser;
    multipartparser_callbacks callbacks;
    unsigned begins, ends, count;
    upload_part_t parts[2];
} upload_capture_t;
void upload_init(upload_capture_t *capture);
void upload_feed(upload_capture_t *capture, const char *bytes, size_t length, size_t chunk);
void upload_complete(upload_capture_t *capture, unsigned parts);
