# Scope and remaining work

Thirty-six cases compile original mpg_transport.c and its public wire header
against pinned CORE types and original nuts_bolts formatting. Plain and framed
transport defaults are separate source-supported builds. Valid peer frames use
the public reference encoder; the CRC check vector123456789=0x29B1 and exact
wire payload/sequence/CRC assertions check the public protocol. Only valid peer frames are used; private MPG_TRANSPORT_TESTING seams are not enabled.

Host stream_open_instance/stream_mpg_register callbacks capture the physical RX
handler and proxy descriptor. They install a public realtime consumer to model
the active byte stream; actual CORE MPG mode switching, broadcast connection
ownership and tool-ACK suspend are not executed. The untested suspend boundary
fails explicitly if reached; it is not a copied implementation. UART output,
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
observable drop counts rather than accessing private counters. No known runtime assertion or sanitizer
exception registered.

Full CORE stream/protocol integration, actual task/IRQ ordering, alternate UART
write fallback, remaining setting validation boundaries, physical
serial/radio reliability and board builds remain. These bounded cases do not establish complete controller behavior or physical
link reliability.
