#include "support/passthru_host.h"
#include "check.h"

int main(void)
{
    prepare_passthru();
    start_passthru();
    CHECK(uart_handler != NULL);
    CHECK(uart_handler('!'));
    finish_passthru_startup();
    CHECK(!uart_handler('!'));
    CHECK(!uart_handler(0));
    return EXIT_SUCCESS;
}
