#include "support/tool_change_host.h"
#include "stream.h"
static stream_rx_buffer_t pending_input;
static unsigned cancel_calls;
static bool cancel_marker;
static int32_t read_pending_input(void)
{
    if(cancel_marker) {
        cancel_marker = false;
        return ASCII_CAN;
    }
    if(pending_input.tail == pending_input.head) return SERIAL_NO_DATA;
    return pending_input.data[pending_input.tail++];
}
static bool suspend_pending_input(bool await) { return stream_rx_suspend(&pending_input, await); }
static void cancel_pending_input(void)
{
    pending_input.tail = pending_input.head;
    cancel_marker = true;
    cancel_calls++;
}
int main(void)
{
    prepare_tool_change();
    memcpy(pending_input.data, "G1X10\n", 6);
    pending_input.head = 6;
    hal.stream.read = read_pending_input;
    hal.stream.suspend_read = suspend_pending_input;
    hal.stream.cancel_read_buffer = cancel_pending_input;
    start_manual_change();
    CHECK(stream_is_rx_suspended() == StreamSuspend_Pending);
    CHECK(hal.stream.read() == SERIAL_NO_DATA);
    CHECK(tool_stream_handler(CMD_TOOL_ACK));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Active && pending_input.backup);
    CHECK(HOST_PARSER_FLAGS.tool_change && pending_input.tail == pending_input.head);
    CHECK(protocol_enqueue_realtime_command(CMD_STOP));
    CHECK(!protocol_exec_rt_system());
    CHECK(sys.cancel && !sys.abort && state_get() == STATE_IDLE);
    CHECK(!HOST_PARSER_FLAGS.tool_change && reset_calls == 1);
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off && !pending_input.backup);
    /* Stop cancels current input, then cancels the saved input restored on unsuspend. */
    CHECK(cancel_calls == 2 && pending_input.tail == pending_input.head);
    CHECK(hal.stream.read() == ASCII_CAN);
    CHECK(hal.stream.read() == SERIAL_NO_DATA);
    CHECK(tool_stream_handler == original_enqueue);
    CHECK(hal.control.interrupt_callback == original_control);
    CHECK(plan_get_current_block() == NULL);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(axis_pulses[axis] == 0);
    return EXIT_SUCCESS;
}
