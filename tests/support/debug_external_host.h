#pragma once
#include "support/engine_host.h"
#include "stream.h"
#include "check.h"
#include <string.h>
static char external_output[512];
static unsigned external_write_calls;
void debug_write(const char *text)
{
    CHECK(strlen(external_output) + strlen(text) < sizeof(external_output));
    strcat(external_output, text); external_write_calls++;
}
