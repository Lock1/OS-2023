#include "lib-header/stdtype.h"
#include "lib-header/fat32.h"
#include "lib-header/stdmem.h"

#define BOOT_BLOCK 0

const uint8_t fs_boot_sector_signature[BLOCK_SIZE] = {
    'B', 'y', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    'L', 'a', 'b', ' ', 'S', 'i', 's', 't', 'e', 'r', ' ', 'I', 'T', 'B', ' ', ' ',
    'M', 'a', 'd', 'e', ' ', 'w', 'i', 't', 'h', ' ', '<', '3', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', '-', 'L', 'o', 'c', 'k', '1', ' ', '2', '0', '2', '3', '\n',
    [BLOCK_SIZE-2] = 'O',
    [BLOCK_SIZE-1] = 'k',
};

bool is_empty_storage(void) {
    struct BlockBuffer boot_sector;
    read_blocks(&boot_sector, 0, 1);
    return memcmp(&boot_sector, fs_boot_sector_signature, BLOCK_SIZE);
}

void initialize_fat32(void) {
    if (is_empty_storage()) {
        write_blocks(fs_boot_sector_signature, BOOT_BLOCK, 1);
        // TODO : Real FAT32 init
    }
}