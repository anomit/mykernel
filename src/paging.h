#ifndef PAGING_H
#define PAGING_H

#include "common.h"

#define NR_PDE 1024
#define NR_PTE 1024

#define PAGE_SIZE 4096

/* 32 bit "blobs" for the paging structures */
typedef u32int pte_t;
typedef u32int pde_t;

/*
 * The following fields are common for both page directory entries
 * and page table entries
 */
#define PAGE_PRESENT_BIT 0
#define PAGE_RW_BIT 1
#define PAGE_US_BIT 2
#define PAGE_PWT_BIT 3
#define PAGE_PCD_BIT 4
#define PAGE_ACCESSED_BIT 5

/*
 * The following fields are available only in page table entries
 */
#define PAGE_DIRTY_BIT 6
#define PAGE_PAT_BIT 7
#define PAGE_GLOBAL_BIT 8

#define unset_present(x) (x & (~(1 << PAGE_PRESENT_BIT)))
#define set_present(x) (x | (1 << PAGE_PRESENT_BIT))

#define unset_rw(x) (x & (~(1 << PAGE_RW_BIT)))
#define set_rw(x) (x | (1 << PAGE_RW_BIT))

/* Supervisor level */
#define set_us(x) (x & (~(1 << PAGE_US_BIT)))
/* User level */
#define unset_us(x) (x | (1 << PAGE_US_BIT))

#define set_accessed(x) (x & (~(1 << PAGE_ACCESSED_BIT)))
#define unset_accessed(x) (x | (1 << PAGE_ACCESSED_BIT))

#define pte_set_dirty(x) (x & (~(1 << PAGE_DIRTY_BIT)))
#define pte_unset_dirty(x) (x | (1 << PAGE_DIRTY_BIT))

void init_paging();

#endif /* PAGING_H */
