#include "paging.h"
#include "kernel_mem.h"

static void init_pagedir(pde_t *);
static void init_pagetable(pte_t *);

void init_paging()
{
    pde_t *kernel_page_directory;
    kernel_page_directory = (pde_t *)kmalloc(sizeof(pde_t) * 1024, 1);
    
    
    init_pagedir(kernel_page_directory);
    
    pte_t *initial_page_table;
    initial_page_table = (pte_t *)kmalloc(sizeof(pte_t) * 1024, 1);

    init_pagetable(initial_page_table);

    kernel_page_directory[0] |= (u32int)initial_page_table;
    kernel_page_directory[0] = set_present(kernel_page_directory[0]);

    asm volatile("mov %0, %%cr3" : : "b"((u32int)kernel_page_directory));
    u32int cr0;
    asm volatile("mov %%cr0, %0" : "=b"(cr0));
    /* CR0.PG = 1 */
    cr0 |= 0x80000000;
    /* ---FAILS HERE--- */
    asm volatile("mov %0, %%cr0" : : "b"(cr0));
}

static void init_pagedir(pde_t *pgdir)
{
    u32int i = 0;
    for ( ; i < 1024; i++)
    {
        /* Clear all bits */
        pgdir[i] ^= pgdir[i];

        pgdir[i] = unset_present(pgdir[i]);
        pgdir[i] = set_rw(pgdir[i]);
        pgdir[i] = set_us(pgdir[i]);
    }
}

static void init_pagetable(pte_t *pgtbl)
{
    u32int i = 0;
    u32int addr = 0;

    for (; i< 1024; i++)
    {
        pgtbl[i] ^= pgtbl[i];

        pgtbl[i] = unset_present(pgtbl[i]);
        pgtbl[i] = set_rw(pgtbl[i]);
        pgtbl[i] = set_us(pgtbl[i]);

        pgtbl[i] |= addr;
        addr += PAGE_SIZE;
    }
}
