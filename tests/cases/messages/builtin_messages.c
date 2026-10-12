#include <string.h>
#include "grbl.h"
#include "messages.h"
#include "check.h"

int main(void)
{
    const message_t *msg = message_get(Message_CriticalEvent);
    CHECK(msg != NULL); CHECK(strcmp(msg->text, "Reset to continue") == 0);
    msg = message_get(Message_None); CHECK(msg != NULL); CHECK(strcmp(msg->text, "") == 0);
    msg = message_get(Message_EStop); CHECK(msg != NULL); CHECK(strstr(msg->text, "Emergency stop") != NULL);
    return EXIT_SUCCESS;
}
