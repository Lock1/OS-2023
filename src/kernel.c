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

static void setup_gdt_and_tss(void) {
    enter_protected_mode(&_gdt_gdtr);
    gdt_install_tss();
    set_tss_register();
}

static void setup_cpu_interrupt_system(void) {
    pic_remap();
    initialize_idt();
    activate_keyboard_interrupt();
}

static void setup_video_output(void) {
    vga_use_video_mode_13h();
    framebuffer_clear();
    vga_use_video_mode_3h();
    framebuffer_clear();
}

static void execute_user_shell(void) {
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

    // Set TSS $esp pointer and jump into shell 
    set_tss_kernel_current_stack();
    kernel_execute_user_program((uint8_t *) 0);
}



// TODO : Audio
// TODO : Video format
// TODO : Encoder-decoder + Player
void kernel_setup(void) {
    setup_gdt_and_tss();           // Setup GDT and flush segment registers
    setup_cpu_interrupt_system();  // IDT, Interrupt & PIC setup
    setup_video_output();          // OS video output setup
    initialize_filesystem_fat32(); // Initialize FAT32 filesystem driver
    execute_user_shell();          // Start user space shell
}