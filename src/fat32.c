#include "lib-header/stdtype.h"
#include "lib-header/fat32.h"

const uint8_t fs_boot_sector_signature[SECTOR_SIZE] = {

};

bool is_empty_storage(void) {
    bool a = 0;
    // read mbr
    return a;
}

void initialize_fat32(void) {
}