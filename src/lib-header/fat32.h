#ifndef _FAT32_H
#define _FAT32_H

#include "disk.h"

#define CLUSTER_SIZE (SECTOR_SIZE*4)

extern const uint8_t fs_boot_sector_signature[SECTOR_SIZE];



struct FSInfo {
    uint32_t lead_signature;
    uint8_t  reserved_1[480];
    uint32_t middle_signature;

    uint32_t last_known_free_cluster_count;
    uint32_t last_free_cluster_number;

    uint8_t  reserved_2[12];
    uint32_t trail_signature;
} __attribute__((packed));




bool is_empty_storage(void);
void initialize_fat32(void);

#endif