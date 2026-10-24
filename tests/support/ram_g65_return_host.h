#pragma once
#include "support/ram_macro_protocol_host.h"
static unsigned explicit_returns;
static void return_g65_file(void)
{
    vfs_file_t *file = hal.stream.file;
    unsigned owner = ram_owner(file);
    CHECK(owner == 1 || owner == 2);
    explicit_returns++;
    CHECK(ram_protocol_eof(file, Status_OK) == Status_OK);
    grbl.on_macro_return = owner == 2 ? return_g65_file : NULL;
}
static status_code_t execute_returning_macro(macro_id_t id, line_number_t line, parameter_words_t words, uint32_t repeats)
{
    status_code_t status = ram_execute_macro(id, line, words, repeats);
    grbl.on_macro_return = return_g65_file;
    return status;
}
