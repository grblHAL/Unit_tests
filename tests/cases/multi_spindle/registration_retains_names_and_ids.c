#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    CHECK(spindle_get_count() == 3);
    CHECK(strcmp(spindle_get_name(0), "primary") == 0);
    CHECK(strcmp(spindle_get_name(1), "secondary") == 0);
    CHECK(strcmp(spindle_get_name(2), "auxiliary") == 0);
    spindle_id_t id = -1;
    CHECK(spindle_get_id(30, &id) && id == 2);
    CHECK(!spindle_get_id(99, &id));
    return EXIT_SUCCESS;
}
