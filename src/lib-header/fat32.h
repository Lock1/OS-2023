#ifndef _FAT32_H
#define _FAT32_H

#include "disk.h"

#define CLUSTER_BLOCK_COUNT 4
#define CLUSTER_SIZE        (BLOCK_SIZE*CLUSTER_BLOCK_COUNT)

extern const uint8_t fs_boot_sector_signature[BLOCK_SIZE];

struct ClusterBuffer {
    uint8_t buf[CLUSTER_SIZE];
} __attribute__((packed));

struct FAT32FileAllocationTable {
    uint32_t cluster_map[512];
} __attribute__((packed));




// Standard 8.3 directory format
// 32 bytes
// https://en.wikipedia.org/wiki/Design_of_the_FAT_file_system#Directory_entry, and click show table
struct FAT32DirectoryEntry {
    char     name[8];
    char     ext[3];
    uint8_t  attribute;
    uint8_t  user_attribute;

    bool     undelete;
    uint16_t create_time;
    uint16_t create_date;
    uint16_t access_date;
    uint16_t cluster_high;
    
    uint16_t modified_time;
    uint16_t modified_date;
    uint16_t cluster_low;
    uint32_t filesize;
} __attribute__((packed));

struct FAT32DirectoryTable {
    struct FAT32DirectoryEntry table[CLUSTER_SIZE / sizeof(struct FAT32DirectoryEntry)];
} __attribute__((packed));



struct FAT32DriverState {
    struct FAT32FileAllocationTable fat_table;
} __attribute__((packed));

uint32_t cluster_to_logical_block_address(uint32_t cluster);
bool is_empty_storage(void);
void initialize_filesystem_fat32(void);

#endif