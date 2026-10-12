#include <string.h>
#include "grbl.h"
#include "messages.h"
#include "check.h"

int main(void)
{
    const message_t *msg = message_get(Message_ExecuteTPW);
    CHECK(msg != NULL); CHECK(msg->type == Message_Warning);
    return EXIT_SUCCESS;
}
