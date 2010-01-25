[GLOBAL gdt_flush]

gdt_flush:
    mov eax, [esp+4] ;get the pointer to the GDT passed to gdt_flush as a parameter
    lgdt [eax]       ;load the GDT pointer
    
    mov ax, 0x10     ;16 bytes offset into GDT gives the kernel data segment
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax
    jmp 0x08:.flush ;Far jump. 8 bytes offset gives the kernel code segment
.flush:
    ret

[GLOBAL idt_flush]

idt_flush:
    mov eax, [esp+4] ;Get pointer to IDT, passed to this function as a parameter
    lidt [eax]   ;load the IDT pointer
    ret
