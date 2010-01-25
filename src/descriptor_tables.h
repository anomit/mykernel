#ifndef DESCIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H

/*This is how a single entry looks in the GDT*/
struct gdt_entry_struct {
        /*lower 16 bits of the limit*/
    u16int limit_low;

     /*lower 16 bits of the base*/
    u16int base_low;
    
    /*the next 8 bits of the base*/
    u8int base_middle; 
    
    u8int access;
    u8int granularity;

    /*last 8 bits of the base*/
    u8int base_high; 
}__attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;

/*Tells the processor about the location of the GDT*/
struct gdt_ptr_struct {
    /*Upper 16 bits of all selector limits*/
    u16int limit;

    /*Address of the first GDT entry, gdt_entry_t struct*/
    u32int base;
}__attribute__((packed));

typedef struct gdt_ptr_struct gdt_ptr_t;

/*Single entry in the IDT*/
struct idt_entry_struct {
    /*Lower 16 bits of address to jump corresponding to the interrupt*/
    u16int base_lo;

    /*kernel segment selector*/
    u16int sel;

    u8int always0; //self explanatory

    u8int flags;

    /*Upper 16 bits of address to jump to*/
    u16int base_hi;
}__attribute__((packed));

typedef struct idt_entry_struct idt_entry_t;

struct idt_ptr_struct {
    u16int limit;
    u32int base;
}__attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;

/*These extern directives let us access the addresses of our ASM ISR handlers*/
extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0 ();
extern void irq1 ();
extern void irq2 ();
extern void irq3 ();
extern void irq4 ();
extern void irq5 ();
extern void irq6 ();
extern void irq7 ();
extern void irq8 ();
extern void irq9 ();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void init_descriptor_tables();

#endif //DESCRIPTOR_TABLES_H
