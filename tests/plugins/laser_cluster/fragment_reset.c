#include "cluster_host.h"
int main(void)
{
    cluster_prepare(false, "G1X");
    char out[128];
    cluster_drain(out, sizeof(out));
    CHECK(!*out);
    grbl.on_reset();
    cluster_source("G1Y6S10:20\n");
    cluster_drain(out, sizeof(out));
    CHECK(!strcmp(out, "G1Y3S10\nG1Y3S20\nG1X0S10\n"));
    CHECK(cluster_previous_resets == 1 && cluster_statuses == 1);
    return 0;
}
