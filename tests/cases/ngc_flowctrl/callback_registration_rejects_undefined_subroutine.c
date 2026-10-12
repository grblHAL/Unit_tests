#include "support/flow_file_host.h"
#include "check.h"

int main(void)
{
    prepare_flow_file();
    CHECK(!ngc_flowctrl_on_endsub_callback(999, NULL));
    close_flow_file();
    return EXIT_SUCCESS;
}
