#include "lib-header/stdtype.h"

void interrupt(uint32_t eax, uint32_t ebx, uint32_t ecx, uint32_t edx) {
    __asm__ volatile("mov %0, %%ebx" : /* <Empty> */ : "r"(ebx));
    __asm__ volatile("mov %0, %%ecx" : /* <Empty> */ : "r"(ecx));
    __asm__ volatile("mov %0, %%edx" : /* <Empty> */ : "r"(edx));
    __asm__ volatile("mov %0, %%eax" : /* <Empty> */ : "r"(eax));
    // Note : gcc usually use %eax as intermediate register, so it need to be last to mov 
    __asm__ volatile("int $0x30");
}

int main(void) {
    int a = 0xDEADBEEF;
    interrupt(0xCAFE, 0xDEADC0DE, a, 0xBABE);
    while (1);

    return 0;
}