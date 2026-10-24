#include "cluster_host.h"
int main(void)
{
    cluster_prepare(false, "");
    grbl.on_report_options(true);
    CHECK(!*cluster_output);
    grbl.on_report_options(false);
    CHECK(strstr(cluster_output, "[CLUSTER:16]") &&
          strstr(cluster_output, "[PLUGIN:LightBurn clusters v0.09]"));
    CHECK(cluster_previous_reports == 2 && cluster_handler_inits == 1);
    grbl.on_report_handlers_init();
    CHECK(cluster_handler_inits == 2);
    return 0;
}
