#include "upload_host.h"
static void missing_directory(char *name, void *context)
{
    CHECK(context == &filename_events && !strcmp(name, "job.nc"));
    filename_events++;
    strcpy(name, "/missing/job.nc");
}
int main(void)
{
    fatfs_prepare();
    fatfs_put_file("/saved.nc", "M2\n", 3);
    http_request_t request;
    file_upload_t *upload = upload_begin(&request);
    http_upload_on_filename_parsed(upload, missing_directory, &filename_events);
    const char body[] =
        "--grbl-upload\r\nContent-Disposition: form-data; name=\"file\"; "
        "filename=\"job.nc\"\r\nContent-Type: text/plain\r\n\r\nG0X0\n\r\n--grbl-upload--\r\n";
    upload_chunks(&request, body, sizeof(body) - 1, 7);
    CHECK(filename_events == 1 && !upload->file.handle && upload->uploaded == 0);
    CHECK(vfs_open("/missing/job.nc", "r") == NULL);
    upload_cleanup(&request);
    upload_readback("/saved.nc", "M2\n", 3);
    return 0;
}
