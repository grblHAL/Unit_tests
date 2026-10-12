#include "support/engine_host.h"
#include "spindle_control.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(!spindle_enumerate_spindles(NULL, NULL));
    return EXIT_SUCCESS;
}
