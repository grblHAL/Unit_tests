#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change();
    start_manual_change();
    CHECK(plan_get_current_block() == NULL);
    CHECK(wake_calls == 0);
    CHECK(select_calls == 1 && selected_next);
    return EXIT_SUCCESS;
}
