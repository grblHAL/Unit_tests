#include "cluster_host.h"
int main(void)
{
    cluster_prepare(false, "G0X1\n");
    char out[128];
    cluster_drain(out, sizeof(out));
    cluster_change(true, "G1Y2S7:7\n");
    cluster_drain(out, sizeof(out));
    CHECK(!strcmp(out, "G1Y1S7\nG1Y1S7\n"));
    CHECK(cluster_previous_streams == 2 && cluster_statuses == 2);
    return 0;
}
