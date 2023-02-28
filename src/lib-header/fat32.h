#ifndef _FAT32_H
#define _FAT32_H

#include "disk.h"

extern const uint8_t fs_boot_sector_signature[SECTOR_SIZE];

bool is_empty_storage(void);
void initialize_fat32(void);

#endif