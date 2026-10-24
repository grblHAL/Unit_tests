# Known regression - 2026-10-24

Source14fdf8de2126316c14d88656f3a19337800ad1c1, original serial.c.
full_realtime fills the supported1023-byte RX capacity, then delivers a realtime
feed-hold byte through the registered SDK UART interrupt. The driver checks ring
space before dispatching realtime commands; the full-buffer branch discards it.
Correct assertion requires the handler invocation without adding to the full ring.
Ordinary realtime filtering, handler replacement and RTS controls pass. No memory
fault, private ring writes or hardware-timing claim.

Upstream should classify realtime bytes before deciding whether ring space is
available. Keep the assertion; remove its exact WILL_FAIL/known_bug label and
this entry after repair. No sanitizer exception.

# Scope

Fourteen cases compile original serial.c/serial.h and real TivaWare headers with
CORE stream.c, stream_passthru, VFS and formatting. Hardware API callbacks capture
UART config, GPIO, FIFO/IRQ and ordered TX. Receive-timeout IRQ and simultaneous
RX/TX cases now deliver enabled SDK event flags through the registered handler;
TX draining preserves RX/timeout masks and ordered incoming bytes. Public stream connect/tool-ACK suspend
uses actual CORE backup/restore; no copied firmware implementation. Original
serial.h selects BACKCHANNEL/UART0 unconditionally; UART1 is not configured by
editing that header or bypassing its definition. RX1024/TX32 are valid power-of-two
host buffers. No UART electrical/timing/error-IRQ or full controller validation.
The source toggles RTS GPIO even in the backchannel build; host capture does not
establish that a physical RTS pin is configured by that board startup.
