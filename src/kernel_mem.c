#include "kernel_mem.h"

extern u32int end;
u32int int_addr = (u32int)&end;

u32int kmalloc(u32int size, int align)
{
    if (align && (int_addr & 0xFFFFF000))
    {
        int_addr &= 0xFFFFF000;
        int_addr += 0x1000;
    }

    u32int temp = int_addr;
    int_addr += size;
    return temp;
}
