;Interrupt service routine wrappers

;This macro creates a stub for an ISR which DOES NOT pass its own error code. 
;Instead adds a dummy errorcode byte
%macro ISR_NOERRCODE 1
    global isr%1
    isr%1:
      cli       ;Disable interrupts
      push byte 0   ;push dummy error code
      push byte %1  ;push the interrupt number
      jmp isr_common_stub
%endmacro

;This macro creates a stub for an ISR which passes its own error code
%macro ISR_ERRCODE 1
    global isr%1
    isr%1:
      cli
      push byte %1
      jmp isr_common_stub
%endmacro

%macro IRQ 2
    global irq%1
    irq%1:
        cli
        push byte 0
        push byte %2
           jmp irq_common_stub
%endmacro

;Only interruprs 8 and 10-14 push error codes onto the stack. Rest require dummy error code
ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

IRQ   0,    32
IRQ   1,    33
IRQ   2,    34
IRQ   3,    35
IRQ   4,    36
IRQ   5,    37
IRQ   6,    38
IRQ   7,    39
IRQ   8,    40
IRQ   9,    41
IRQ  10,    42
IRQ  11,    43
IRQ  12,    44
IRQ  13,    45
IRQ  14,    46
IRQ  15,    47

;In isr.c
extern isr_handler
extern irq_handler

;The common ISR stub. It saves the processor state, sets up for kernel mode segments, calls the fault handler function in C and restores the stack frame
isr_common_stub:
    pusha       ;push all

    mov ax, ds
    push eax

    mov ax, 0x10    ;the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop ebx     ;restore the original data segment descriptor
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa        ;pop all
    add esp, 8  ;cleans up pushed error code and ISR number
    sti
    iret        ;pops CS, EIP, EFLAGS, SS and SP

;The common IRQ stub
irq_common_stub:
    pusha       ;push edi, esi, ebp, esp, eax, ebx, ecx, edx

    mov ax, ds  ;lower 16 bits of eax = ds
    push eax    ;save the data segment descriptor

    mov ax, 0x10    ;kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call irq_handler

    pop ebx     ;get the original data segment descriptor
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa        ;pop edi, esp, ebp, eax, ebx, ecx, edx
    add esp, 8
    sti
    iret
