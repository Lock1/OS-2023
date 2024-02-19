#include "lib-header/cpu/interrupt.h"
#include "lib-header/cpu/portio.h"
#include "lib-header/cpu/gdt.h"
#include "lib-header/driver/keyboard.h"
#include "lib-header/driver/text-io-module/textio.h"
#include "lib-header/driver/framebuffer.h"
#include "lib-header/filesystem/fat32.h"
#include "lib-header/stdmem.h"

// TODO : Use dispatch table style to decouple this with keyboard and other

struct TSSEntry _interrupt_tss_entry = {
    .ss0  = GDT_KERNEL_DATA_SEGMENT_SELECTOR,
};

void set_tss_kernel_current_stack(void) {
    uint32_t stack_ptr;
    // Reading base stack frame instead esp
    __asm__ volatile ("mov %%ebp, %0": "=r"(stack_ptr) : /* <Empty> */);
    // Add 8 because 4 for ret address and other 4 is for stack_ptr variable
    _interrupt_tss_entry.esp0 = stack_ptr + 8; 
}

void main_interrupt_handler(struct InterruptFrame frame) {
    switch (frame.int_number) {
        case PAGE_FAULT:
            __asm__("hlt");
            break;
        case PIC1_OFFSET + IRQ_TIMER:
            pic_ack(0);
            break;
        case PIC1_OFFSET + IRQ_KEYBOARD:
            keyboard_isr();
            break;
        case 0x30:
            syscall(frame.cpu, frame.int_stack);
            break;
    }
}

void syscall(struct CPURegister cpu, __attribute__((unused)) struct InterruptStack info) {
    if (cpu.general.eax == 0) {
        struct FAT32DriverRequest request = *(struct FAT32DriverRequest*) cpu.general.ebx;
        *((int8_t*) cpu.general.ecx) = read(request);
    } else if (cpu.general.eax == 1) {
        struct FAT32DriverRequest request = *(struct FAT32DriverRequest*) cpu.general.ebx;
        *((int8_t*) cpu.general.ecx) = read_directory(request);
    } else if (cpu.general.eax == 4) {
        keyboard_state_activate();
        __asm__("sti"); // Due IRQ is disabled when main_interrupt_handler() called
        while (is_keyboard_blocking());
        char buf[KEYBOARD_BUFFER_SIZE];
        get_keyboard_buffer(buf);
        memcpy((char *) cpu.general.ebx, buf, cpu.general.ecx);
    } else if (cpu.general.eax == 5) {
        puts((char *) cpu.general.ebx, cpu.general.ecx, cpu.general.edx);
    } else if (cpu.general.eax == 6) {
        struct FAT32DriverRequest request = *(struct FAT32DriverRequest*) cpu.general.ebx;
        *((int8_t*) cpu.general.ecx) = read(request);
        framebuffer_draw_sis_image(request.buf, 320, 200);

        __asm__("hlt"); // FIXME : Yes, very quick solution
    } else if (cpu.general.eax == 7) {
        struct FAT32DriverRequest request = *(struct FAT32DriverRequest*) cpu.general.ebx;
        *((int8_t*) cpu.general.ecx) = read(request);
        // TODO : Drawer & Parser
        framebuffer_play_ter_video(request.buf);

        __asm__("hlt"); // FIXME : Another quick solution
    }
}

void io_wait(void) {
    out(0x80, 0);
}

void pic_ack(uint8_t irq) {
    if (irq >= 8)
        out(PIC2_COMMAND, PIC_ACK);
    out(PIC1_COMMAND, PIC_ACK);
}

void activate_keyboard_interrupt(void) {
    // TODO: Split this timer
    out(PIC1_DATA, in(PIC1_DATA) & ~(1 << IRQ_KEYBOARD) & ~(1 << IRQ_TIMER));
}

void pic_remap(void) {
    // Starts the initialization sequence in cascade mode
    out(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); 
    io_wait();
    out(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    out(PIC1_DATA, PIC1_OFFSET); // ICW2: Master PIC vector offset
    io_wait();
    out(PIC2_DATA, PIC2_OFFSET); // ICW2: Slave PIC vector offset
    io_wait();
    out(PIC1_DATA, 0b0100);      // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    io_wait();
    out(PIC2_DATA, 0b0010);      // ICW3: tell Slave PIC its cascade identity (0000 0010)
    io_wait();

    out(PIC1_DATA, ICW4_8086);
    io_wait();
    out(PIC2_DATA, ICW4_8086);
    io_wait();

    // Restore masks
    out(PIC1_DATA, PIC_DISABLE_ALL_MASK);
    out(PIC2_DATA, PIC_DISABLE_ALL_MASK);
}