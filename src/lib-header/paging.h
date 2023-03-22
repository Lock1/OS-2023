#ifndef _PAGING_H
#define _PAGING_H

#include "stdtype.h"

#define PAGE_ENTRY_COUNT 1024

// Decision : 4 MiB paging mode, less data structure, it seems less complex than 4KB
extern struct PageDirectory _paging_kernel_page_directory;


// 32-bit structure
struct PageDirectoryEntryFlag {
    uint8_t present_bit        : 1;
    uint8_t read_write_bit     : 1;
    uint8_t user_bit           : 1;
    uint8_t use_write_through  : 1;
    uint8_t disable_caching    : 1;
    uint8_t accessed_bit       : 1;
    uint8_t dirty_bit          : 1;
    uint8_t use_pagesize_4_mb  : 1;
} __attribute__((packed));

// Warning: Address must be aligned in 4 KB or 4 MB
// Check Intel Manual 3a - Ch 4 Paging - Figure 4-4 PDE: 4MB page
struct PageDirectoryEntry {
    struct PageDirectoryEntryFlag flag;
    uint8_t  global_page    : 1;
    uint8_t  reserved_1     : 3;
    uint8_t  use_pat        : 1;
    
    uint8_t  higher_address;
    uint8_t  reserved_2     : 1;
    uint16_t lower_address  : 10;
} __attribute__((packed));

struct PageDirectory {
    struct PageDirectoryEntry table[PAGE_ENTRY_COUNT];
} __attribute__((packed));


void init_kernel_page_directory(void);

extern void kernel_tlb_flush(void);

#endif