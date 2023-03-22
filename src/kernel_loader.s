global low_loader                             ; the entry symbol for ELF
global enter_protected_mode                   ; go to protected mode
extern kernel_setup                           ; kernel
extern _gdt_gdtr
extern _paging_kernel_page_directory          ; kernel page directory
extern _kernel_start
extern _kernel_end

KERNEL_VIRTUAL_BASE equ 0xC0000000
KERNEL_STACK_SIZE   equ 4194304                 ; size of stack in bytes
MAGIC_NUMBER        equ 0x1BADB002              ; define the magic number constant
FLAGS               equ 0x0                     ; multiboot flags
CHECKSUM            equ -MAGIC_NUMBER           ; calculate the checksum
                                                ; (magic number + checksum + flags should equal 0)

section .bss
align 4                                       ; align at 4 bytes
kernel_stack:                                 ; label points to beginning of memory
    resb KERNEL_STACK_SIZE                    ; reserve stack for the kernel

section .multiboot                            ; GRUB multiboot header
align 4                                       ; the code must be 4 byte aligned
    dd MAGIC_NUMBER                           ; write the magic number to the machine code,
    dd FLAGS                                  ; the flags,
    dd CHECKSUM                               ; and the checksum

section .data
align 4096
global TEMP_PAGE_DIRECTORY
TEMP_PAGE_DIRECTORY:
    ; Map the first 4mb physical memory to first 4mb virtual memory. Otherwise, when paging is enabled, eip points to, 0x100004 for example, and MMU is not gonna know how to translate 
    ; this address into phsyical mem address, because our PDE doesn't tell MMU how to find it.
    dd 0x00000083
    times(0x300 - 1) dd 0
    dd 0x00000083
    times(1024 - 0x300 - 1) dd 0 

section .setup.text                           ; start of the text (code) section
low_loader equ (loader - KERNEL_VIRTUAL_BASE)
loader:                                   ; the loader label (defined as entry point in linker script)
setup_paging:
    mov edi, TEMP_PAGE_DIRECTORY - KERNEL_VIRTUAL_BASE
    mov esi, 0
    
    ; First 4 MB
    mov edx, esi
    or  edx, 0x83           ; Present writable flag
    mov [edi], edx

;   Higher half mapping
    ; on page directory corresponding 0xC000 0000, map those into physical address starting from 0
    mov edi, TEMP_PAGE_DIRECTORY - KERNEL_VIRTUAL_BASE + 4 * 0x300 
    mov esi, 0

    ; First 4 MB
    mov edx, esi
    or  edx, 0x83           ; Present writable flag
    mov [edi], edx



    ; Identity mapping
; paging_init_loop_1:
;     cmp [_kernel_start], esi
;     jl  paging_init_loop_2
;     cmp [_kernel_end - KERNEL_VIRTUAL_BASE], esi
;     jge paging_init_loop_3

;     ; Get and set page directory entry
;     mov edx, esi
;     or  edx, 0x3           ; Present writable flag
;     mov [edi], edx

; paging_init_loop_2:
;     add esi, 4*1024*1024   ; Move into next page frame address 
;     add edi, 4             ; Next page directory entry index
;     loop paging_init_loop_1

; paging_init_loop_3:

    ; Set CR3 (CPU page register)
    mov eax, TEMP_PAGE_DIRECTORY - KERNEL_VIRTUAL_BASE
    mov cr3, eax

    ; Use 4 MB paging
    mov eax, cr4
    or  eax, 0x00000010    ; PSE (4 MB paging)
    mov cr4, eax

    ; Enable paging
    mov eax, cr0
    ; mov ecx, 0xDEADBEEF
    ; hlt
    or  eax, 0x80000000   ; PG flag
    mov cr0, eax
    mov eax, 0xDEADBEEF
    hlt

    mov esp, kernel_stack + KERNEL_STACK_SIZE ; setup stack register to proper location
    ; call kernel_setup
.loop:
    jmp .loop                                 ; loop forever


; More details: https://en.wikibooks.org/wiki/X86_Assembly/Protected_Mode
enter_protected_mode:
    ; Load GDT from GDTDescriptor
    cli
    mov  eax, _gdt_gdtr - KERNEL_VIRTUAL_BASE
    lgdt [eax]
    
    ; Set Protection Enable bit-flag in Control Register 0 (CR0)
    ; Or in other words: Switch to protected mode
    mov  eax, cr0
    or   eax, 1
    mov  cr0, eax

    ; Far jump to update cs register
    ; Warning: Invalid GDT will raise exception in any instruction below
    jmp 0x8:flush_cs
flush_cs:
    ; Update all segment register
    mov ax, 10h
    mov ss, ax
    mov ds, ax
    mov es, ax