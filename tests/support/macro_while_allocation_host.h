#pragma once
#define NAMED_MACRO_BODY "(Arm while)\nO10WHILE[#1GT0]\n#100=[#100+1]\n#1=[#1-1]\nO10ENDWHILE\n"
#include "support/embedded_macro_protocol_host.h"
static bool fail_next_malloc, inject_while_failure = true;
static unsigned failed_malloc_calls, arm_comments;
void *__real_malloc(size_t size);
void *__wrap_malloc(size_t size)
{
    if(fail_next_malloc) {
        fail_next_malloc = false;
        failed_malloc_calls++;
        return NULL;
    }
    return __real_malloc(size);
}
static on_gcode_message_ptr previous_comment;
static status_code_t arm_while_failure(char *text)
{
    if(strcmp(text, "Arm while") == 0) {
        if(arm_comments++ == 0 && inject_while_failure) fail_next_malloc = true;
        return Status_OK;
    }
    return previous_comment ? previous_comment(text) : Status_OK;
}
static status_code_t observe_named_eof(vfs_file_t *file, status_code_t status)
{
    // The CORE named-sub EOF handler runs before this observer and owns close.
    if(file != ram_macro_files[0])
        CHECK(hal.stream.file != file);
    return status;
}
static void prepare_while_assets(void)
{
    register_named_macro_assets();
    grbl.on_file_end = observe_named_eof;
    previous_comment = grbl.on_gcode_comment;
    grbl.on_gcode_comment = arm_while_failure;
}
static inline void run_while_allocation_protocol(void)
{
    ram_prepare_assets = prepare_while_assets;
    ram_sender_query = "$G\nO<fixture>CALL[2]\n$G\n";
    run_ram_root_protocol("#1=99\n#100=0\n#101=0\nO<fixture>CALL[2]\n#101=7\n");
}
