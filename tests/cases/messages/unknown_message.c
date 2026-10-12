#include <string.h>
#include "grbl.h"
#include "messages.h"
#include "check.h"

int main(void)
{
    CHECK(message_get(Message_NextMessage) == NULL);
    CHECK(message_get((message_code_t)250) == NULL);
    return EXIT_SUCCESS;
}
