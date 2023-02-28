#include "lib-header/stdtype.h"
#include "lib-header/fat32.h"
#include "lib-header/stdmem.h"

#define BOOT_SECTOR 0

const uint8_t fs_boot_sector_signature[SECTOR_SIZE] = {
    'B', 'y', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    'L', 'a', 'b', ' ', 'S', 'i', 's', 't', 'e', 'r', ' ', 'I', 'T', 'B', ' ', ' ',
    'M', 'a', 'd', 'e', ' ', 'w', 'i', 't', 'h', ' ', '<', '3', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', '-', 'L', 'o', 'c', 'k', '1', ' ', '2', '0', '2', '3', '\n',
    [SECTOR_SIZE-2] = 'O',
    [SECTOR_SIZE-1] = 'k',
};

bool is_empty_storage(void) {
    struct SectorBuffer boot_sector;
    read_sectors(&boot_sector, 0, 1);
    return memcmp(&boot_sector, fs_boot_sector_signature, SECTOR_SIZE);
}

void initialize_fat32(void) {
    if (is_empty_storage()) {
        write_sectors(fs_boot_sector_signature, BOOT_SECTOR, 1);
        // TODO : Real FAT32 init
    }
}