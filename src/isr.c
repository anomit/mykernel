/*High level interrupt service routines and interrupt request handlers*/

#include "isr.h"
#include "common.h"
#include "monitor.h"

isr_t interrupt_handlers[256];

void register_interrupt_handler(u8int n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

void isr_handler(registers_t regs)
{
    if (interrupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
    else
    {
        monitor_write("received interrupt: ");
        monitor_write_dec(regs.int_no);
        monitor_put('\n');
    }
}

void irq_handler(registers_t regs)
{
    /*Send an EOI signal to the PICs if this interrupt involved the slaves*/
    if(regs.int_no >= 40)
    {
        /*Send reset signal to slave*/
        outb(0xA0, 0x20);
    }
    
    /*send reset signal to master and also slave if necessary*/
    outb(0x20, 0x20);

    if(interrupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}
