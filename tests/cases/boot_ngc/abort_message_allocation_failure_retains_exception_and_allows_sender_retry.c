#include "support/boot_host.h"
#include <stdlib.h>

static bool reject_message, missing_message_seen;
static unsigned failed_allocations, abort_lines;
void *__real_malloc(size_t size);
void *__wrap_malloc(size_t size)
{
    if(reject_message) {
        CHECK(size == sizeof("Requested stop"));
        reject_message = false;
        failed_allocations++;
        return NULL;
    }
    return __real_malloc(size);
}
static void observe_abort_line(void)
{
    if(boot_program[boot_reads] != '(') return;
    CHECK(hal.stream.is_connected());
    if(++abort_lines == 1) reject_message = true;
    else {
        char error[32];
        snprintf(error, sizeof(error), "error:%u", (unsigned)Status_UserException);
        CHECK(failed_allocations == 1 && !reject_message);
        CHECK(strstr(engine_output, error) != NULL);
        CHECK(strstr(engine_output, "Requested stop") == NULL);
        CHECK(strstr(engine_output, "[GC:") != NULL);
        missing_message_seen = true;
    }
}
int main(void)
{
    boot_before_read = observe_abort_line;
    boot_program = "(ABORT,Requested stop)\n$G\n(ABORT,Requested stop)\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(abort_lines == 2 && missing_message_seen && failed_allocations == 1);
    char error[32];
    snprintf(error, sizeof(error), "error:%u", (unsigned)Status_UserException);
    const char *first = strstr(engine_output, error);
    CHECK(first != NULL && strstr(first + strlen(error), error) != NULL);
    const char *message = strstr(engine_output, "[MSG:Error: Requested stop]");
    CHECK(message != NULL && strstr(message + strlen("[MSG:Error: Requested stop]"), "Requested stop") == NULL);
    CHECK(strstr(engine_output, "[GC:") != NULL);
    CHECK(state_get() == STATE_IDLE && sys.alarm == Alarm_None);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    return EXIT_SUCCESS;
}
