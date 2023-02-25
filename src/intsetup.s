extern generic_interrupt_handler

%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
    push    dword 0                 ; push 0 as error code
    push    dword %1                ; push the interrupt number
    jmp     call_generic_handler    ; jump to the common handler
%endmacro

%macro error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
    push    dword %1
    jmp     call_generic_handler
%endmacro

call_generic_handler:
    ; Before interrupt_handler_n above, stack will have these value that pushed by CPU
    ; [esp + 12] eflags
    ; [esp + 8 ] cs
    ; [esp + 4 ] eip
    ; [esp + 0 ] error code

    ; CPURegister
    push    esp
    push    ebp
    push    edx
    push    ecx
    push    ebx
    push    eax


    ; call the C function
    call    generic_interrupt_handler

    ; restore the registers
    pop     eax
    pop     ebx
    pop     ecx
    pop     edx
    pop     ebp
    pop     esp

    ; restore the esp (interrupt number & error code)
    add     esp, 8

    ; return to the code that got interrupted
    iret



; Interrupt handlers
no_error_code_interrupt_handler 8       ; create handler for interrupt 0
