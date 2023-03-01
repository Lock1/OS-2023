#include "lib-header/stdtype.h"
#include "lib-header/fat32.h"
#include "lib-header/stdmem.h"

static struct FAT32DriverState fat32driver_state = {0};

const uint8_t fs_signature[BLOCK_SIZE] = {
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
    return memcmp(&boot_sector, fs_signature, BLOCK_SIZE);
}

void create_fat32(void) {
    write_blocks(fs_signature, BOOT_SECTOR, 1);

    // Reserved values
    fat32driver_state.fat_table.cluster_map[0] = CLUSTER_0_VALUE;
    fat32driver_state.fat_table.cluster_map[1] = CLUSTER_1_VALUE;

    // Root
    fat32driver_state.fat_table.cluster_map[ROOT_CLUSTER_NUMBER] = FAT32_FAT_END_OF_FILE;
    
    // Write new valid File Allocation Table
    write_clusters(&fat32driver_state.fat_table, FAT_CLUSTER_NUMBER, 1);

    // Write root directory table
    struct FAT32DirectoryTable root_dir_table;
    init_directory_table(&root_dir_table, ROOT_CLUSTER_NUMBER);
    write_clusters(&root_dir_table, ROOT_CLUSTER_NUMBER, 1);
}

void initialize_filesystem_fat32(void) {
    if (is_empty_storage())
        create_fat32();
    else {
        read_clusters(&fat32driver_state.fat_table, FAT_CLUSTER_NUMBER, 1);
    }
}