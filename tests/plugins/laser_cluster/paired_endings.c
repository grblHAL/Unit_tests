#include "cluster_host.h"
int main(void)
{
    cluster_prepare(false, "G1X2S7:7\r\nG1Y2S8:8\n\r");
    char out[128];
    cluster_drain(out, sizeof(out));
    CHECK(!strcmp(out, "G1X1S7\nG1X1S7\nG1Y1S8\nG1Y1S8\n"));
    CHECK(cluster_statuses == 2);
    return 0;
}
