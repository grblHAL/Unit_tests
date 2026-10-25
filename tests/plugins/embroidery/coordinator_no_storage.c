#include "job_host.h"
int main(void)
{
    job_storage = false;
    job_prepare();
    CHECK(job_settings == NULL && job_warnings == 1);
    CHECK(grbl.on_file_open == NULL);
    CHECK(embroidery_get_thread_color(0) == NULL);
    hal.driver_reset();
    CHECK(job_resets == 1);
    return 0;
}
