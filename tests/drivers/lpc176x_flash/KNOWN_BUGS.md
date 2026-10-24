# LPC176x flash scope

Original sourceea6e9f78fa349e86fbd58a203760b614f513684a and CORE
b01f481072edecac33d5e40c25869359a5b3fa1f remain unchanged. No known assertion
or sanitizer allowances are registered for these storage cases.

The suite compiles original src/flash.c with native-width RAM pointers and
original32-bit physical flash addresses. A dedicated
process-local mapping provides its fixed0x78000 flash region; VirtualAlloc on
Windows and MAP_FIXED_NOREPLACE on Linux refuse to replace existing mappings.
IAP/IRQ boundaries are simulated with signatures/status values checked against
the source checkout's NXP headers. Callbacks validate sector29, destination,
write size, preparation/blank-state requirements and restored IRQ state.

Cases cover erased reads,1024/4096-byte write/readback, unchanged suppression,
failure of either prepare/erase/copy stage and retry after copy failure. The2048
configured-size case intentionally supplies4096 readable source bytes because
the implementation programs4096 whenever size is not1024. It verifies that
explicit padded-buffer behavior only. It does not establish safety for a normal
CORE2048 allocation (CORE defaults to2048), nor a driver/CORE integration pass.
An unpadded buffer is not used to reproduce an overread. Allocation/copy-size
compatibility needs maintainer/firmware integration work and remains a TODO.

Original code overwrites the earlier IAP return codes and continues. The model
preserves preparation/blank requirements so failed prerequisite cases still
return false through the final copy status. These are not evidence that original
code stops immediately on earlier errors. All such paths must restore IRQs and
must not report a successful copy when no bytes were programmed.

No actual NXP ROM/SDK execution, ARM firmware build, interrupts disabled on a real
CPU, flash endurance or board timing is established. Linux mapping and hosted
multilib steps remain unverified until their actual workflow runs. Host macros
avoid Windows On/NEAR naming collisions without changing CORE or firmware.

The initial32-bit Windows fixture collided intermittently with an existing low
address allocation. This module never converts its RAM pointer to a32-bit integer,
so that host-width constraint was unnecessary. The native64-bit process retains
normal ASLR and refuses occupied mappings. Only original source int-to-pointer-cast warnings
stay nonfatal/visible for the known low physical address; fixtures remain strict.
This does not change the ROM ABI or establish a64-bit firmware implementation.
