#ifndef _PAGING_H
#define _PAGING_H

#include "stdtype.h"

#define PAGE_ENTRY_COUNT 1024

// Decision : 4 MiB paging mode, less data structure, it seems less complex than 4KB
extern struct PageDirectory _paging_kernel_page_directory;


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
    uint8_t  higher_address : 3;   // Need to be 3 for pleasing gcc packed rule
    uint8_t  reserved_2     : 4;
    uint16_t lower_address  : 10;
} __attribute__((packed));

struct PageDirectory {
    struct PageDirectoryEntry table[PAGE_ENTRY_COUNT];
} __attribute__((packed));

#endif