global loader                   ; the entry symbol for ELF
global load_gdt
extern kmain

MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
FLAGS        equ 0x0            ; multiboot flags
CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum
								; (magic number + checksum + flags should equal 0)
KERNEL_STACK_SIZE equ 4096      ; size of stack in bytes

section .bss
kernel_stack:                   ; label points to beginning of memory
	resb KERNEL_STACK_SIZE      ; reserve stack for the kernel

section .text:                  ; start of the text (code) section
align 4
	dd MAGIC_NUMBER             ; write the magic number to the machine code,
	dd FLAGS                    ; the flags,
	dd CHECKSUM                 ; and the checksum

loader:                         ; the loader label (defined as entry point in linker script)
	mov esp, kernel_stack + KERNEL_STACK_SIZE   ; point esp to the start of the stack (end of memory area)
	call kmain

load_gdt:
	cli
	lgdt [esp+4]
	ret
