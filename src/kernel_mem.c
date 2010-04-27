#include "kernel_mem.h"

u32int placement_addr = 0x00000000;

u32int kmalloc(u32int size, int align)
{
    if (align && (placement_addr & 0xFFFFF000))
    {
        placement_addr &= 0xFFFFF000;
        placement_addr += 0x1000;
    }

    u32int temp = placement_addr;
    placement_addr += size;
    return temp;
}
