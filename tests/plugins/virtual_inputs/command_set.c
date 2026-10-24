#include "vinput_host.h"
int main(void)
{
    vi_start(true);
    CHECK(vi_command("0,1") == Status_OK);
    CHECK(virtual_inputs_get().mask == 1 && strstr(output, "PROBE=1,TLS=0"));
    CHECK(vi_command("1,1") == Status_OK);
    CHECK(virtual_inputs_get().mask == 3);
    CHECK(vi_command("0,0") == Status_OK);
    CHECK(virtual_inputs_get().mask == 2);
    CHECK(vi_command("1,0") == Status_OK);
    CHECK(virtual_inputs_get().mask == 0);
    CHECK(strstr(output, "PROBE_SET=0,PROBE_CLR=0,TLS_SET=0,TLS_CLR=0"));
    return 0;
}
