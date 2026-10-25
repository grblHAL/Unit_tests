#include "files_host.h"
static void perform(http_request_t *request, files_request_t *p, const char *action,
                    const char *status)
{
    p->action = action;
    files_action(request);
    char response[4096];
    files_response(response, sizeof(response));
    CHECK(!p->status[0] && strstr(response, status));
}
int main(void)
{
    http_request_t request;
    files_request_t p = {.path = "/", .filename = "jobs"};
    files_prepare(&request, &p);
    perform(&request, &p, "createdir", "jobs created");
    perform(&request, &p, "createdir", "jobs already exists!");
    fatfs_put_file("/jobs/cut.nc", "M2\n", 3);
    perform(&request, &p, "deletedir", "Error deleting jobs!");
    files_readback("/jobs/cut.nc", "M2\n", 3);
    CHECK(vfs_unlink("/jobs/cut.nc") == 0);
    perform(&request, &p, "deletedir", "jobs deleted");
    vfs_stat_t stat;
    CHECK(vfs_stat("/jobs", &stat) != 0 && p.headers == 4);
    return 0;
}
