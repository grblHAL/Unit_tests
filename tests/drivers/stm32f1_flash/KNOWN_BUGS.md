# STM32F1 flash scope

Original sourcec22362352f6abeea94897bb0346ae8042cdf3210 and CORE
b01f481072edecac33d5e40c25869359a5b3fa1f remain unchanged. No expected assertion
or sanitizer allowances are registered for these valid storage cases.

Original Src/flash.c executes as a32-bit host target with linker-style region and
page-count symbols. Shared STM32 halfword fixtures retain the F1 HAL erase layout
(Banks/PageAddress/NbPages), one-page configuration and original call signatures.
The F1 main/HAL include names are provided by host SDK boundaries; no production
or CORE aliases/patches are used. Actual HAL/ARM instructions are not executed.

Cases cover read/copy, unchanged suppression, erase retry/failure, either
halfword failure, subsequent recovery and word-aligned configured buffer sizes.
F1 does not inspect unlock status; the HAL model returns a locked-erase error
rather than asserting. Two failed erase attempts and the final lock operation
correctly return false without programming. No immediate-unlock-abort claim is
made. Existing F4/F7 layout/lock assertions remain separate in the shared fixture.

These selected helper results do not establish controller boot/NVS integration,
board linker geometry, physical flash/cache/IRQ behavior or other driver modules.
No firmware build or whole-driver coverage is claimed.
