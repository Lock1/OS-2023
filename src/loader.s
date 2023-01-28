global loader                        ; the entry symbol for ELF
global launch_protected_mode         ; go to protected mode
extern kernel_setup                  ; kernel
extern gdt


KERNEL_STACK_SIZE equ 4096           ; size of stack in bytes
MAGIC_NUMBER      equ 0x1BADB002     ; define the magic number constant
FLAGS             equ 0x0            ; multiboot flags
CHECKSUM          equ -MAGIC_NUMBER  ; calculate the checksum
                                     ; (magic number + checksum + flags should equal 0)

section .bss
align 4                              ; align at 4 bytes
kernel_stack:                        ; label points to beginning of memory
    resb KERNEL_STACK_SIZE           ; reserve stack for the kernel

section .text                        ; start of the text (code) section
align 4                              ; the code must be 4 byte aligned
    dd MAGIC_NUMBER                  ; write the magic number to the machine code,
    dd FLAGS                         ; the flags,
    dd CHECKSUM                      ; and the checksum


loader:                                       ; the loader label (defined as entry point in linker script)
    mov esp, kernel_stack + KERNEL_STACK_SIZE ; setup stack register to proper location
    call kernel_setup
.loop:
    jmp .loop                                 ; loop forever

launch_protected_mode:
    mov eax, gdt
    lgdt [eax]
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    mov ax, 10h
    mov ss, ax
    mov ds, ax
    mov es, ax

    jmp 0x8:flush_cs
flush_cs:
    ret