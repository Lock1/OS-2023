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


void syscall(uint32_t eax, uint32_t ebx, uint32_t ecx, uint32_t edx) {
    __asm__ volatile("mov %0, %%ebx" : /* <Empty> */ : "r"(ebx));
    __asm__ volatile("mov %0, %%ecx" : /* <Empty> */ : "r"(ecx));
    __asm__ volatile("mov %0, %%edx" : /* <Empty> */ : "r"(edx));
    __asm__ volatile("mov %0, %%eax" : /* <Empty> */ : "r"(eax));
    // Note : gcc usually use %eax as intermediate register, so it need to be last to mov 
    __asm__ volatile("int $0x30");
}

size_t strlen(const char *ptr) {
    uint32_t i = 0;
    while (ptr[i] != '\0')
        i++;
    return i;
}

void readfs(struct FAT32DriverRequest request) {
    int retcode;
    syscall(0, (uint32_t) &request, (uint32_t) &retcode, 0);
}

void readdir(struct FAT32DriverRequest request) {
    int retcode;
    syscall(1, (uint32_t) &request, (uint32_t) &retcode, 0);
}

void fgets(char *buf, uint32_t count) {
    syscall(4, (uint32_t) buf, count, 0);
}

void puts(char *buf, uint8_t color) {
    syscall(5, (uint32_t) buf, strlen(buf), color);
}

uint8_t strcmp(const char *a, const char *b) {
    if (strlen(a) != strlen(b))
        return 1;
    else {
        uint32_t i = 0;
        while (a[i] != '\0') {
            if (a[i] != b[i])
                return 1;
            i++;
        }
        return 0;
    }
}



int main(void) {
    struct ClusterBuffer cl           = {0};
    struct FAT32DriverRequest request = {
        .buf                   = &cl,
        .name                  = "ikanaide",
        .ext                   = "\0\0\0",
        .parent_cluster_number = 2,
        .buffer_size           = CLUSTER_SIZE,
    };
    readfs(request);

    char buf[16];
    while (TRUE) {
        puts("Brush@OS-IF2230", BIOS_LIGHT_GREEN);
        puts(":", BIOS_GRAY);
        puts("/", BIOS_LIGHT_BLUE);
        puts("$ ", BIOS_GRAY);
        fgets(buf, 16);

        if (!strcmp(buf, "cat ikanaide")) {
            // *Kind* of mockup, but still working properly
            puts((char*) &cl, BIOS_YELLOW);
            puts("\n", BIOS_YELLOW);
        }
    }

    return 0;
}