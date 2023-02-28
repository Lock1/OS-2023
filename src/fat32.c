#include "lib-header/stdtype.h"
#include "lib-header/fat32.h"
#include "lib-header/stdmem.h"

#define BOOT_SECTOR         0

#define CLUSTER_0_VALUE     0x0FFFFFF0
#define CLUSTER_1_VALUE     0x0FFFFFFF

// EOF also double as valid cluster
#define FAT32_END_OF_FILE   0x0FFFFFFF
#define FAT32_EMPTY_ENTRY   0x00000000

#define FAT_CLUSTER_NUMBER  1
#define ROOT_CLUSTER_NUMBER 2

#define ATTR_SUBDIRECTORY   0b00010000
#define UATTR_NOT_EMPTY     0b10101010


static struct FAT32DriverState fat32driver_state = {0};


const uint8_t fs_boot_sector_signature[BLOCK_SIZE] = {
    'B', 'y', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    'L', 'a', 'b', ' ', 'S', 'i', 's', 't', 'e', 'r', ' ', 'I', 'T', 'B', ' ', ' ',
    'M', 'a', 'd', 'e', ' ', 'w', 'i', 't', 'h', ' ', '<', '3', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', '-', 'L', 'o', 'c', 'k', '1', ' ', '2', '0', '2', '3', '\n',
    [BLOCK_SIZE-2] = 'O',
    [BLOCK_SIZE-1] = 'k',
};

uint32_t cluster_to_logical_block_address(uint32_t cluster) {
    return cluster * CLUSTER_BLOCK_COUNT;
}

// Max block_count = 255 => Max cluster_count = 63
void write_clusters(const void *ptr, uint32_t cluster_number, uint8_t cluster_count) {
    write_blocks(ptr, cluster_to_logical_block_address(cluster_number), cluster_count*CLUSTER_BLOCK_COUNT);
}

void read_clusters(void *ptr, uint32_t cluster_number, uint8_t cluster_count) {
    read_blocks(ptr, cluster_to_logical_block_address(cluster_number), cluster_count*CLUSTER_BLOCK_COUNT);
}

void init_directory_table(struct FAT32DirectoryTable *dir_table, uint32_t parent_dir_cluster) {
    dir_table->table[0].cluster_high   = 0xFFFF & (parent_dir_cluster >> 16);
    dir_table->table[0].cluster_low    = 0xFFFF & parent_dir_cluster;
    dir_table->table[0].user_attribute = UATTR_NOT_EMPTY;
}

bool is_empty_storage(void) {
    struct BlockBuffer boot_sector;
    read_blocks(&boot_sector, 0, 1);
    return memcmp(&boot_sector, fs_boot_sector_signature, BLOCK_SIZE);
}

void create_fat32(void) {
    write_blocks(fs_boot_sector_signature, BOOT_SECTOR, 1);

    // Reserved values
    fat32driver_state.fat_table.cluster_map[0] = CLUSTER_0_VALUE;
    fat32driver_state.fat_table.cluster_map[1] = CLUSTER_1_VALUE;

    // Root
    fat32driver_state.fat_table.cluster_map[ROOT_CLUSTER_NUMBER] = FAT32_END_OF_FILE;
    
    // Write new valid File Allocation Table
    write_clusters(&fat32driver_state.fat_table, FAT_CLUSTER_NUMBER, 1);
}

void initialize_filesystem_fat32(void) {
    if (is_empty_storage())
        create_fat32();
    else {
        read_clusters(&fat32driver_state.fat_table, FAT_CLUSTER_NUMBER, 1);
    }
}