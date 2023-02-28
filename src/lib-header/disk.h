#ifndef _DISK_H
#define _DISK_H

#include "stdtype.h"

// ATA PIO status codes
#define ATA_STATUS_BSY   0x80
#define ATA_STATUS_RDY   0x40
#define ATA_STATUS_DRQ   0x08
#define ATA_STATUS_DF    0x20
#define ATA_STATUS_ERR   0x01

#define SECTOR_SIZE      512
#define HALF_SECTOR_SIZE (SECTOR_SIZE/2)

/**
 * ATA PIO logical block address read sectors. Will blocking until read is completed.
 * Note: ATA PIO will use 2-bytes per read/write operation
 * 
 * @param ptr Pointer for storing reading data, this pointer should point to already allocated memory location.
 *            With allocated size positive integer multiple of SECTOR_SIZE, ex: buf[1024]
 * @param logical_block_address Block address to read data from. Use LBA addressing
 * @param sector_count How many sector to read, starting from sector logical_block_address to lba-1
 */
void read_sectors(void *ptr, uint32_t logical_block_address, uint8_t sector_count);

/**
 * ATA PIO logical block address write sectors. Will blocking until write is completed.
 * Note: ATA PIO will use 2-bytes per read/write operation
 *
 * @param ptr Pointer to data that to be written into disk. Memory pointed should be positive integer multiple of SECTOR_SIZE
 * @param logical_block_address Block address to write data into. Use LBA addressing
 * @param sector_count How many sector to write, starting from sector logical_block_address to lba-1
 */
void write_sectors(void *ptr, uint32_t logical_block_address, uint8_t sector_count);

#endif