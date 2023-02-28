#include "lib-header/disk.h"
#include "lib-header/portio.h"

static void ATA_busy_wait() {
    while (in(0x1F7) & ATA_STATUS_BSY);
}

static void ATA_DRQ_wait() {
    while (!(in(0x1F7) & ATA_STATUS_RDY));
}

void read_sectors(void *ptr, uint32_t logical_block_address, uint8_t sector_count) {
    ATA_busy_wait();
    out(0x1F6, 0xE0 | ((logical_block_address >> 24) & 0xF));
    out(0x1F2, sector_count);
    out(0x1F3, (uint8_t) logical_block_address);
    out(0x1F4, (uint8_t) (logical_block_address >> 8));
    out(0x1F5, (uint8_t) (logical_block_address >> 16));
    out(0x1F7, 0x20);

    uint16_t *target = (uint16_t*) ptr;

    for (uint32_t i = 0; i < sector_count; i++) {
        ATA_busy_wait();
        ATA_DRQ_wait();
        for (uint32_t j = 0; j < HALF_SECTOR_SIZE; j++)
            target[j] = in16(0x1F0);
        // Note : uint16_t => 2 bytes, HALF_SECTOR_SIZE*2 = SECTOR_SIZE with pointer arithmetic
        target += HALF_SECTOR_SIZE;
    }
}

void write_sectors(const void *ptr, uint32_t logical_block_address, uint8_t sector_count) {
    ATA_busy_wait();
    out(0x1F6, 0xE0 | ((logical_block_address >> 24) & 0xF));
    out(0x1F2, sector_count);
    out(0x1F3, (uint8_t) logical_block_address);
    out(0x1F4, (uint8_t) (logical_block_address >> 8));
    out(0x1F5, (uint8_t) (logical_block_address >> 16));
    out(0x1F7, 0x30);

    for (uint32_t i = 0; i < sector_count; i++) {
        ATA_busy_wait();
        ATA_DRQ_wait();
        /* Note : uint16_t => 2 bytes, i is current sector number to write
           HALF_SECTOR_SIZE*i = sector_offset with pointer arithmetic
        */
        for (uint32_t j = 0; j < HALF_SECTOR_SIZE; j++)
            out16(0x1F0, ((uint16_t*) ptr)[HALF_SECTOR_SIZE*i + j]);
    }
}