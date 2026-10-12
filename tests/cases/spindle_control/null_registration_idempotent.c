#include "support/engine_host.h"
#include "spindle_control.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    spindle_id_t id = spindle_add_null();
    CHECK(id >= 0);
    CHECK(spindle_add_null() == id);
    CHECK(spindle_get_count() == 0);
    return EXIT_SUCCESS;
}
