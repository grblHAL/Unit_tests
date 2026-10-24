# Known command ordering regression - 2026-10-25

`plugin_mpg_transport.m1_core_command_burst` retains the correct order assertion
for a single valid Data frame containing `$I\n$G\n$$\n`. CORE
b01f481072edecac33d5e40c25869359a5b3fa1f stream.c copies each completed passive
command to the same `mpg.rx_buf->input`, then queues `stream_mpg_write` without a
command snapshot. The foreground tasks therefore deliver `$$`, `$$`, `$$` to the
system-command boundary rather than `$I`, `$G`, `$$`. All three tasks execute;
there is no malformed frame, buffer-boundary probe or sanitizer allowance.

The test executes original stream and transport code with MPG_BUFFER_SIZE=128.
Its bounded FIFO host task delivery matches grbllib.c's append order; the actual
CORE task allocator/executor and actual system command implementation are not
linked. The recording system boundary exposes the strings it receives. The result
establishes this deferred ownership defect in host integration, not a hardware
incident or a full controller job result. Separate fragmented/single-command,
CRLF, empty-command, G-code-rejection and handler-error/recovery controls pass.

A proposed firmware repair must retain each completed command until its queued
execution consumes it (including normal queue capacity/error behavior). No repair
is applied here. Remove only this exact WILL_FAIL/known_bug label and this entry
when the correct order assertion passes against a repaired original source.

# Scope and remaining work

Forty-five cases compile original mpg_transport.c and its public wire header
against pinned CORE types and original nuts_bolts formatting. Plain and framed
transport defaults are separate source-supported builds. Valid peer frames use
the public reference encoder; the CRC check vector123456789=0x29B1 and exact
wire payload/sequence/CRC assertions check the public protocol. Only valid peer frames are used; private MPG_TRANSPORT_TESTING seams are not enabled.

Thirty-six capture cases replace stream registration and install a realtime
consumer to model an active byte stream. Their untested suspend boundary fails
explicitly if reached. Nine additional cases instead link actual CORE stream,
stream_passthru, VFS, strutils and formatting sources. Original APIs register and
claim a simulated UART, install the actual passive filter and copy the descriptor.
They exercise busy refusal, mode switching/restoration, baud-table changes,
broadcast/active output ownership and queued passive status requests. The original
null stream supplies the primary console baseline. MPG_BUFFER_SIZE=0 explicitly
disables passive command buffering in six cases. Two more plain/framed cases
enable the normal128-byte buffer for fragmented commands, CRLF, G-code rejection
and handler errors; one framed burst case retains the ordering regression above. Status formatting emits a host marker and
protocol/task/time/UART operations remain explicit test boundaries. Tool-ACK
suspension is not executed; active primary-driver ownership still needs review. UART output,
clock, settings registration and NVS are simulated. Tests cover ordered traffic,
duplicate suppression, channel separation, fragmented valid frames, ACK/NAK,
timeout/retry budget, normal receive backpressure, TX chunking, reset, baud,
resource failures and diagnostics. Registered setting pointers and on_changed hooks
now cover acknowledgement floors during queued output and transport persistence
through save/load; a soft reset retains the applied transport. Output discard
checks sequence separation and rejects stale acknowledgements for fresh data.
Byte-only UART output is checked in both modes; restore persists defaults,
runtime payload limits retain complete ordered data, and the updated attempt
budget bounds retransmission without resetting a healthy link. Seven further
local callback cases cover delay-time polling, realtime handler lifecycle, muted
RX decoding and public byte output in both modes. The no-consumer case asserts
observable drop counts rather than accessing private counters. One correct CORE
command-order assertion is expected to fail; no sanitizer exception registered.

Full CORE protocol/parser/task integration, manual-tool
stream ownership, actual task/IRQ ordering, remaining setting validation, physical
serial/radio reliability and board builds remain. These bounded cases do not establish complete controller behavior or physical
link reliability.
