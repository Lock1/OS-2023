extern main_interrupt_handler
global isr_stub_table

%macro no_error_code_interrupt_handler 1
interrupt_handler_%1:
    push    dword 0                 ; push 0 as error code
    push    dword %1                ; push the interrupt number
    jmp     call_generic_handler    ; jump to the common handler
%endmacro

%macro error_code_interrupt_handler 1
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
    call    main_interrupt_handler

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
    ; at this point, stack should be structured like this
    ; [esp], [esp+4], [esp+8]
    ;   eip,   cs,    eflags
    ; improper value will cause invalid return address & register
    iret



; Interrupt handlers
no_error_code_interrupt_handler 0
no_error_code_interrupt_handler 1
no_error_code_interrupt_handler 2
no_error_code_interrupt_handler 3
no_error_code_interrupt_handler 4
no_error_code_interrupt_handler 5
no_error_code_interrupt_handler 6
no_error_code_interrupt_handler 7
error_code_interrupt_handler    8
no_error_code_interrupt_handler 9
error_code_interrupt_handler    10
error_code_interrupt_handler    11
error_code_interrupt_handler    12
error_code_interrupt_handler    13
error_code_interrupt_handler    14
no_error_code_interrupt_handler 15
no_error_code_interrupt_handler 16
error_code_interrupt_handler    17
no_error_code_interrupt_handler 18
no_error_code_interrupt_handler 19
no_error_code_interrupt_handler 20
no_error_code_interrupt_handler 21
no_error_code_interrupt_handler 22
no_error_code_interrupt_handler 23
no_error_code_interrupt_handler 24
no_error_code_interrupt_handler 25
no_error_code_interrupt_handler 26
no_error_code_interrupt_handler 27
no_error_code_interrupt_handler 28
no_error_code_interrupt_handler 29
error_code_interrupt_handler    30
no_error_code_interrupt_handler 31


isr_stub_table:
    %assign i 0 
    %rep    32 
    dd interrupt_handler_%+i
    %assign i i+1 
    %endrep