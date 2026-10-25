#include "files_host.h"
int main(void)
{
    http_request_t request;
    files_request_t p = {.uri = "jobs/cut.nc"};
    files_prepare(&request, &p);
    vfs_drive_t *drive = fs_get_root_drive();
    CHECK(drive && drive->removable && fs_get_sd_drive());
    CHECK(fs_get_flash_drive(false) == NULL);
    CHECK(!strcmp(fs_download_handler(&request, drive), "jobs/cut.nc"));
    vfs_drive_t mounted = {.path = "/sd"};
    CHECK(!strcmp(fs_download_handler(&request, &mounted), "/sd/jobs/cut.nc"));
    CHECK(fs_download_handler(&request, NULL) == NULL && !strcmp(p.status, "404 Not Found"));
    p.status[0] = 0;
    CHECK(fs_action_handler(&request, NULL) == NULL && !strcmp(p.status, "400 Bad Request"));
    return 0;
}
