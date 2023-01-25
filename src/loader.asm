global loader                   ; the entry symbol for ELF
global enter_protected_mode
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

enter_protected_mode:
	cli
	lgdt [ebp+8]
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	
	mov eax, 10h
    mov ds, eax
    mov ss, eax
    mov es, eax

	jmp 0x8:flush_cs

	ret

flush_cs:
	
