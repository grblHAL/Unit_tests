#include "upload_host.h"
int main(void)
{
    fatfs_prepare();
    CHECK(vfs_mkdir("/jobs") == 0);
    http_request_t request;
    file_upload_t *upload = upload_begin(&request);
    http_upload_on_filename_parsed(upload, upload_name, &filename_events);
    const char body[] =
        "--grbl-upload\r\nContent-Disposition: form-data; "
        "name=\"path\"\r\n\r\n/jobs\r\n--grbl-upload\r\nContent-Disposition: form-data; "
        "name=\"size\"\r\n\r\n3\r\n--grbl-upload\r\nContent-Disposition: form-data; name=\"file\"; "
        "filename=\"job.nc\"\r\nContent-Type: text/plain\r\n\r\nM2\n\r\n--grbl-upload--\r\n";
    upload_chunks(&request, body, sizeof(body) - 1, 11);
    CHECK(upload->state == Upload_Complete && upload->size == 3 && upload->uploaded == 3);
    CHECK(!strcmp(upload->path, "/jobs") && filename_events == 1);
    upload_readback("/jobs/cut.nc", "M2\n", 3);
    upload_cleanup(&request);
    return 0;
}
