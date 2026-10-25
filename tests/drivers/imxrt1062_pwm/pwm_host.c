#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#undef NEAR
#else
#include <sys/mman.h>
#endif
#include "pwm_host.h"
volatile uint32_t F_BUS_ACTUAL = 150000000;
uint32_t pwm_mux[64];
volatile uint32_t *portConfigRegister(uint8_t pin)
{
    CHECK(pin < 64);
    return &pwm_mux[pin];
}
void pwm_prepare(void)
{
#ifdef _WIN32
    void *region =
        VirtualAlloc((void *)0x40000000, 0x400000, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#else
    void *region = mmap((void *)0x40000000, 0x400000, PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);
#endif
    CHECK(region == (void *)0x40000000);
    memset(region, 0, 0x400000);
}
