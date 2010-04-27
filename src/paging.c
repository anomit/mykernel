#include "paging.h"
#include "kernel_mem.h"

static void init_pagedir(pde_t *);
static void init_pagetable(pte_t *);
static void setup_kernel_paging();

void init_paging()
{
    setup_kernel_paging();
    u32int cr0;
    asm volatile("mov %%cr0, %0" : "=b"(cr0));
    /* CR0.PG = 1 */
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0" : : "b"(cr0));
}

/*
 * Identity mapping the first 8 MB of physical memory
 * PS: Idea shamelessly copied from Linux
 */
static void setup_kernel_paging()
{
    u32int i = 0;
    u32int frame_addr = 0x00000;
    pde_t *kernel_page_directory;
    kernel_page_directory = (pde_t *)kmalloc(sizeof(pde_t) * NR_PDE , 1);
    init_pagedir(kernel_page_directory);
    
    pte_t *initial_page_table1;
    initial_page_table1 = (pte_t *)kmalloc(sizeof(pte_t) * NR_PTE, 1);
    init_pagetable(initial_page_table1);
    for( ; i < NR_PTE; i++)
    {
        initial_page_table1[i] = frame_addr;
        initial_page_table1[i] = set_present(initial_page_table1[i]);
        frame_addr += PAGE_SIZE;
    }

    pte_t *initial_page_table2;
    initial_page_table2 = (pte_t *)kmalloc(sizeof(pte_t) * NR_PTE, 1);
    init_pagetable(initial_page_table2);
    for(i = 0; i < NR_PTE; i++)
    {
        initial_page_table2[i] = frame_addr;
        initial_page_table2[i] = set_present(initial_page_table2[i]);
        frame_addr += PAGE_SIZE;
    }

    kernel_page_directory[0] |= (u32int)initial_page_table1;
    kernel_page_directory[0] = set_present(kernel_page_directory[0]);
    kernel_page_directory[1] != (u32int)initial_page_table2;
    kernel_page_directory[1] = set_present(kernel_page_directory[1]);

    asm volatile("mov %0, %%cr3" : : "b"((u32int)kernel_page_directory));
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

    for (; i< 1024; i++)
    {
        pgtbl[i] ^= pgtbl[i];
        pgtbl[i] = set_rw(pgtbl[i]);
        pgtbl[i] = set_us(pgtbl[i]);

    }
}
