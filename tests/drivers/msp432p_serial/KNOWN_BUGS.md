# Known regression - 2026-10-24

Rechecked 2026-11-24: MSP432P401R45aa53e38c1efe20a241deda1ddbbeabbdd83098,
COREa53a16a4d756f12a27006152ba3a99b5ec46b2c7, original serial.c.
mute_preserves_tx queues normal output while the UART is busy, then uses public
stream.disable_rx(true). serialDisable assigns the whole IE register to0,
clearing TXIE as well as RXIE; disable_rx(false) only restores RXIE. Correct
assertion requires TXIE to remain enabled and queued output to finish. Idle RX
mute/unmute, queued TX, blocking and full-ring controls pass. Upstream should
change only the RX interrupt bit. Keep the assertion and remove only its exact
WILL_FAIL/known_bug label and this entry after repair. No sanitizer allowance.

# Scope

Fifteen primary-UART cases compile original serial.c, driver.h, BoosterPack map,
TI device and CMSIS headers distributed in the explicitly pinned Energia SDK
source checkout. No claim of latest official SDK version. Host-owned mapped
peripheral and NVIC memory preserves real vendor register layouts/constants.
Original CMSIS NVIC priority/enable functions execute against that owned memory.
A forced host header first includes the real driver header normally, then
rebinds exactly the two CPU interrupt intrinsic macros to observable host calls;
no include guard, firmware function or legacy CORE type is replaced. This models
critical-section requests, not CPU interrupt scheduling or hardware timing.

Original CORE stream registration/claim/close, connection and tool-ACK suspend
backup/restore execute. Hardware RXBUF/IV and BUSY changes are explicit host IRQ
stimuli; queued TX writes are observed per IRQ. Primary RX32/TX16 are supported
power-of-two configurations. Native RAM pointers are retained; mapped MCU register
addresses are below4GB. A mapping must fail safely if occupied.

Secondary UART, RTS bit-band mode, target linking and physical boards remain.
Source review: SERIAL2_MOD expands to A2, but its status-table entry is under
#if SERIAL2_MOD while properties/functions use #ifdef SERIAL2_MOD. Do not open
that secondary instance or force a status-table memory failure; establish/fix its
supported guard contract first. No secondary runtime coverage is claimed.

The host target is 32-bit, matching the MCU pointer width. This keeps the real
0xE0000000 NVIC mapping outside the 64-bit Linux ASan shadow gap. Mappings still
require the requested address without replacing existing memory; no register
addresses or firmware sources are changed.
