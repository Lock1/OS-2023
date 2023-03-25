#include "lib-header/stdtype.h"
#include "lib-header/fat32.h"

#define BIOS_BLACK         0x0
#define BIOS_BLUE          0x1
#define BIOS_GREEN         0x2
#define BIOS_CYAN          0x3
#define BIOS_RED           0x4
#define BIOS_MAGENTA       0x5
#define BIOS_BROWN         0x6
#define BIOS_GRAY          0x7

#define BIOS_DARK_GRAY     0x8
#define BIOS_LIGHT_BLUE    0x9
#define BIOS_LIGHT_GREEN   0xA
#define BIOS_LIGHT_CYAN    0xB
#define BIOS_LIGHT_RED     0xC
#define BIOS_LIGHT_MAGENTA 0xD
#define BIOS_YELLOW        0xE
#define BIOS_WHITE         0xF


void interrupt(uint32_t eax, uint32_t ebx, uint32_t ecx, uint32_t edx) {
    __asm__ volatile("mov %0, %%ebx" : /* <Empty> */ : "r"(ebx));
    __asm__ volatile("mov %0, %%ecx" : /* <Empty> */ : "r"(ecx));
    __asm__ volatile("mov %0, %%edx" : /* <Empty> */ : "r"(edx));
    __asm__ volatile("mov %0, %%eax" : /* <Empty> */ : "r"(eax));
    // Note : gcc usually use %eax as intermediate register, so it need to be last to mov 
    __asm__ volatile("int $0x30");
}

size_t strlen(char *ptr) {
    uint32_t i = 0;
    while (ptr[i] != '\0')
        i++;
    return i;
}

void puts(char *buf, uint8_t color) {
    interrupt(5, (uint32_t) buf, strlen(buf), color);
}

int main(void) {
    char buf[16];
    while (TRUE) {
        puts("Brush@OS-IF2230", BIOS_LIGHT_GREEN);
        puts(":", BIOS_GRAY);
        puts("/", BIOS_LIGHT_BLUE);
        puts("$ ", BIOS_GRAY);
        interrupt(4, (uint32_t) buf, 16, 0);
    }

    return 0;
}