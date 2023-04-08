#include "lib-header/cpu/portio.h"
#include "lib-header/cpu/gdt.h"
#include "lib-header/cpu/idt.h"
#include "lib-header/cpu/interrupt.h"
#include "lib-header/driver/vga.h"
#include "lib-header/driver/framebuffer.h"
#include "lib-header/driver/keyboard.h"
#include "lib-header/driver/disk.h"
#include "lib-header/driver/text-io-module/textio.h"
#include "lib-header/filesystem/fat32.h"
#include "lib-header/memory/paging.h"
#include "lib-header/kernel.h"
#include "lib-header/stdtype.h"
#include "lib-header/stdmem.h"

void kernel_setup(void) {
    enter_protected_mode(&_gdt_gdtr);
    pic_remap();
    initialize_idt();
    activate_keyboard_interrupt();
    framebuffer_clear();
    framebuffer_set_cursor(0, 0);
    initialize_filesystem_fat32();
    gdt_install_tss();
    set_tss_register();

    // Allocate first 4 MiB virtual memory
    allocate_single_user_page_frame((uint8_t*) 0);

    // Write shell into memory
    struct FAT32DriverRequest request = {
        .buf                   = (uint8_t*) 0,
        .name                  = "shell",
        .ext                   = "\0\0\0",
        .parent_cluster_number = ROOT_CLUSTER_NUMBER,
        .buffer_size           = 0x100000,
    };
    read(request);
    vga_use_video_mode_13h();

    // Set TSS $esp pointer and jump into shell 
    set_tss_kernel_current_stack();
    kernel_execute_user_program((uint8_t *) 0);

    while (TRUE);
}