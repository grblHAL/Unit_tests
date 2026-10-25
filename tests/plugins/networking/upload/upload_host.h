#pragma once
#include "fatfs_host.h"
#include "http_upload.h"
file_upload_t *upload_begin(http_request_t *request);
void upload_chunks(http_request_t *request, const char *bytes, size_t length, size_t chunk);
void upload_readback(const char *name, const void *bytes, size_t size);
void upload_cleanup(http_request_t *request);
extern unsigned filename_events;
void upload_name(char *name, void *context);
