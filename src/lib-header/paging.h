#ifndef _PAGING_H
#define _PAGING_H

#include "stdtype.h"

#define PAGE_ENTRY_COUNT 1024

// Operating system page directory, using page size 4 MiB
extern struct PageDirectory _paging_kernel_page_directory;
// Linker variable  _linker_kernel_start : Pointing to kernel starting address
extern uint32_t *_linker_kernel_start;
// Linker variable  _linker_kernel_end : Pointing to kernel end address
extern uint32_t *_linker_kernel_end;


/**
 * Page Directory Entry Flag
 * 
 * @param present_bit       Indicate whether this entry is exist or not
 * @param write_bit         Is write allowed in this page frame
 * @param user_bit          Is this page privilege user? 0 indicate kernel
 * @param use_write_through Page write through policy
 * @param disable_caching   Page-level caching policy
 * @param accessed_bit      Indicate whether software accessing this page (MMU can edit this)
 * @param dirty_bit         Indicate whether software written something in this page (MMU can edit this)
 * @param use_pagesize_4_mb For this project always 1, indicate page size 4 KiB or 4 MiB
 */
struct PageDirectoryEntryFlag {
    uint8_t present_bit        : 1;
    uint8_t write_bit          : 1;
    uint8_t user_bit           : 1;
    uint8_t use_write_through  : 1;
    uint8_t disable_caching    : 1;
    uint8_t accessed_bit       : 1;
    uint8_t dirty_bit          : 1;
    uint8_t use_pagesize_4_mb  : 1;
} __attribute__((packed));

/**
 * Page Directory Entry, for page size 4 MB.
 * Check Intel Manual 3a - Ch 4 Paging - Figure 4-4 PDE: 4MB page
 * 
 * @param flag            Contain 8-bit page directory entry flag
 * @param global_page     Is this page translation global (also cannot be flushed)
 * @param reserved_1      Reserved bit
 * @param use_pat         Whether use PAT or not, unused for this project
 * @param higher_address  Higher address for page, unused for this project 
 *    (note: Intel manual show minimum at least 4 bit, but due gcc angry with bitfield packing rule and its unused, we will use 3)
 * @param reserved_2      Reserved bit
 * @param lower_address   10-bit lower address, note directly correspond with 4 MiB memory (= 0x40 0000 = 1 with 22 zeros, 
 *    which is exactly PageDirectoryEntry bit-22 to 31 = lower_address)
 */
struct PageDirectoryEntry {
    struct PageDirectoryEntryFlag flag;
    uint8_t  global_page    : 1;
    uint8_t  reserved_1     : 3;
    
    uint8_t  use_pat        : 1;
    uint8_t  higher_address : 3;   // Need to be exactly 3 for pleasing gcc packed rule
    uint8_t  reserved_2     : 4;
    uint16_t lower_address  : 10;
} __attribute__((packed));

/**
 * Page Directory, contain array of PageDirectoryEntry.
 * Note: This data structure not only can be manipulated by kernel, 
 *   MMU operation, TLB hit & miss also affecting this data structure (dirty, accessed bit, etc).
 * Warning: Address must be aligned in 4 KB (listed on Intel Manual), use __attribute__((aligned(0x1000))), 
 *   unaligned definition of PageDirectory will cause triple fault
 * 
 * @param table Fixed-width array of PageDirectoryEntry with size PAGE_ENTRY_COUNT
 */
struct PageDirectory {
    struct PageDirectoryEntry table[PAGE_ENTRY_COUNT];
} __attribute__((packed));

/**
 * update_page_directory,
 * Edit _paging_kernel_page_directory with respective parameter
 * 
 * @param physical_addr Physical address to map
 * @param virtual_addr  Virtual address to map
 * @param flag          Page entry flags
 */
void update_page_directory(void *physical_addr, void *virtual_addr, struct PageDirectoryEntryFlag flag);

/**
 * flush_single_tlb, 
 * invalidate page that contain virtual address in parameter
 * 
 * @param virtual_addr Virtual address to flush
 */
void flush_single_tlb(void *virtual_addr);

#endif