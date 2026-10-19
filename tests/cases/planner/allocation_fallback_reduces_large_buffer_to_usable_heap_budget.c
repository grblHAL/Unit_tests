#include "support/planner_allocation_host.h"
int main(void)
{
    check_bounded_planner_fallback(256, 128);
    return EXIT_SUCCESS;
}
