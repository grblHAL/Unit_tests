# Known defects and test scope

No runtime defect is classified for this host-tested partition-storage module.
Original driver source 0b2d3e1bb7da3b0ae0e03490b71275374eb84c67 is unchanged.

The original main/nvs.c uses simulated ESP partition APIs and real CORE HAL
types. SDK attribute macros/types/constants are narrowly declared at the host
boundary, not a bundled ESP-IDF SDK or firmware build. No physical erase, UART
ISR/cache timing or complete-driver correctness is claimed.

Cases check named-partition discovery, absent/uninitialized storage, exact
read/write bytes, erase/write failures, failed-read invalidation, reinitialization
and write retry. Every simulated erase checks all256 byte values against the
original temporary realtime filter; handler restoration is checked after success
and failure. The normal handler must not run while simulated flash is busy.
Fixtures and this production source compile with strict warnings. No sanitizer
allowances. Other driver modules/boards remain inventory work.
