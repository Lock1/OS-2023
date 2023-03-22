global loader                                 ; the entry symbol for ELF
global enter_protected_mode                   ; go to protected mode
extern kernel_setup                           ; kernel
extern _paging_kernel_page_directory          ; kernel page directory
extern _kernel_start
extern _kernel_end

KERNEL_STACK_SIZE equ 4194304                 ; size of stack in bytes
MAGIC_NUMBER      equ 0x1BADB002              ; define the magic number constant
FLAGS             equ 0x0                     ; multiboot flags
CHECKSUM          equ -MAGIC_NUMBER           ; calculate the checksum
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


section .setup.text                           ; start of the text (code) section
loader:                                       ; the loader label (defined as entry point in linker script)
    mov esp, kernel_stack + KERNEL_STACK_SIZE ; setup stack register to proper location
    
    ; Setup paging
    mov edi, _paging_kernel_page_directory - 0xC0000000
    mov esi, 0

    ; First 4 MB
    mov edx, esi
    or  edx, 0x43           ; Present writable flag
    mov [edi], edx

    add esi, 4*1024*1024
    add edi, 4

    ; Second 4 MB
    mov edx, esi
    or  edx, 0x43           ; Present writable flag
    mov [edi], edx

    add esi, 4*1024*1024
    add edi, 4

    ; Second 4 MB
    mov edx, esi
    or  edx, 0x43           ; Present writable flag
    mov [edi], edx

    add esi, 4*1024*1024
    add edi, 4

    ; Second 4 MB
    mov edx, esi
    or  edx, 0x43           ; Present writable flag
    mov [edi], edx

    add esi, 4*1024*1024
    add edi, 4

    ; Second 4 MB
    mov edx, esi
    or  edx, 0x43           ; Present writable flag
    mov [edi], edx

    add esi, 4*1024*1024
    add edi, 4

    ; Sixth 4 MB
    mov edx, esi
    or  edx, 0x43           ; Present writable flag
    mov [edi], edx






;   Higher half mapping
    mov esi, 0
    ; on page directory corresponding 0xC000 0000, map those into physical address starting from 0
    mov edi, _paging_kernel_page_directory - 0xC0000000 + 4 * 0x300 

    ; First 4 MB
    mov edx, esi
    or  edx, 0x43           ; Present writable flag
    mov [edi], edx

    add esi, 4*1024*1024
    add edi, 4

    ; Second 4 MB
    mov edx, esi
    or  edx, 0x43           ; Present writable flag
    mov [edi], edx

    add esi, 4*1024*1024
    add edi, 4

    ; Second 4 MB
    mov edx, esi
    or  edx, 0x43           ; Present writable flag
    mov [edi], edx

    add esi, 4*1024*1024
    add edi, 4

    ; Second 4 MB
    mov edx, esi
    or  edx, 0x43           ; Present writable flag
    mov [edi], edx

    add esi, 4*1024*1024
    add edi, 4

    ; Second 4 MB
    mov edx, esi
    or  edx, 0x43           ; Present writable flag
    mov [edi], edx

    add esi, 4*1024*1024
    add edi, 4

    ; Sixth 4 MB
    mov edx, esi
    or  edx, 0x43           ; Present writable flag
    mov [edi], edx


    ; Identity mapping
; paging_init_loop_1:
;     cmp [_kernel_start], esi
;     jl  paging_init_loop_2
;     cmp [_kernel_end - 0xC0000000], esi
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
    ; Map first 4 MB (including framebuffer) as present and writable
    mov  ecx, 0x43
    mov [_paging_kernel_page_directory - 0xC0000000 + 0x300 * 4], ecx

    ; Set CR3 (CPU page register)
    mov ecx, _paging_kernel_page_directory - 0xC0000000
    mov cr3, ecx

    ; Use 4 MB paging
    mov ecx, cr4
    or  ecx, 0x00000010    ; PSE (4 MB paging)
    mov cr4, ecx
    ; hlt
    ; Enable paging
    mov ecx, cr0
    or  ecx, 0x80000000    ; PG flag
    mov cr0, ecx
    hlt
    
    call kernel_setup
.loop:
    jmp .loop                                 ; loop forever

section .text
; More details: https://en.wikibooks.org/wiki/X86_Assembly/Protected_Mode
enter_protected_mode:
    ; Load GDT from GDTDescriptor
    cli
    mov  eax, [esp+4]
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

    ret
