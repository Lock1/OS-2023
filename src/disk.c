#include "lib-header/disk.h"
#include "lib-header/portio.h"

#define STATUS_BSY  0x80
#define STATUS_RDY  0x40
#define STATUS_DRQ  0x08
#define STATUS_DF   0x20
#define STATUS_ERR  0x01

#define SECTOR_SIZE 512

static void ATA_busy_wait() {
    while (in(0x1F7) & STATUS_BSY);
}

static void ATA_DRQ_wait() {
    while (!(in(0x1F7) & STATUS_RDY));
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

    for (uint32_t j = 0; j < sector_count; j++) {
        ATA_busy_wait();
        ATA_DRQ_wait();
        for (uint32_t i = 0; i < 256; i++)
            target[i] = in16(0x1F0);
        target += SECTOR_SIZE;
    }
}

void write_sectors(void *ptr, uint32_t logical_block_address, uint8_t sector_count) {
    ATA_busy_wait();
    out(0x1F6, 0xE0 | ((logical_block_address >> 24) & 0xF));
    out(0x1F2, sector_count);
    out(0x1F3, (uint8_t) logical_block_address);
    out(0x1F4, (uint8_t) (logical_block_address >> 8));
    out(0x1F5, (uint8_t) (logical_block_address >> 16));
    out(0x1F7, 0x30);

    for (uint32_t j = 0; j < sector_count; j++) {
        ATA_busy_wait();
        ATA_DRQ_wait();
        for (uint32_t i = 0; i < SECTOR_SIZE; i++)
            out(0x1F0, ((uint8_t*) ptr)[i]);
    }
}