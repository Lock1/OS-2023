#include "lib-header/paging.h"

struct PageDirectory _paging_kernel_page_directory = {0};


void init_kernel_page_directory(void) {
    for (int i = 0; i < PAGE_ENTRY_COUNT; i++) {
        _paging_kernel_page_directory.table[i].lower_address          = i;   // Max 1024
        _paging_kernel_page_directory.table[i].higher_address         = 0;   // Max 256
        _paging_kernel_page_directory.table[i].flag.present_bit       = TRUE;
        _paging_kernel_page_directory.table[i].flag.read_write_bit    = TRUE;
        _paging_kernel_page_directory.table[i].flag.use_pagesize_4_mb = TRUE;
    }
}