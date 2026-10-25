#include "upload_host.h"
unsigned filename_events;
file_upload_t *upload_begin(http_request_t *request)
{
    memset(request, 0, sizeof(*request));
    file_upload_t *upload = http_upload_start(request, "grbl-upload", true);
    CHECK(upload && request->private_data == upload && request->on_request_completed);
    CHECK(upload->state == Upload_Parsing && upload->to_fatfs);
    return upload;
}
void upload_chunks(http_request_t *request, const char *bytes, size_t length, size_t chunk)
{
    CHECK(chunk > 0);
    for (size_t offset = 0; offset < length;)
    {
        size_t count = length - offset < chunk ? length - offset : chunk;
        CHECK(http_upload_chunk(request, bytes + offset, count) == count);
        offset += count;
    }
}
void upload_readback(const char *name, const void *bytes, size_t size)
{
    uint8_t actual[256];
    CHECK(size <= sizeof(actual));
    vfs_file_t *file = vfs_open(name, "r");
    CHECK(file && file->size == size);
    CHECK(vfs_read(actual, 1, sizeof(actual), file) == size);
    CHECK(!memcmp(actual, bytes, size));
    vfs_close(file);
}
void upload_cleanup(http_request_t *request)
{
    CHECK(request->private_data && request->on_request_completed);
    request->on_request_completed(request->private_data);
    request->private_data = NULL;
}
void upload_name(char *name, void *context)
{
    CHECK(context == &filename_events && !strcmp(name, "job.nc"));
    filename_events++;
    strcpy(name, "/jobs/cut.nc");
}
