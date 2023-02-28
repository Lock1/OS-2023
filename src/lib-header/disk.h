#ifndef _DISK_H
#define _DISK_H

#include "stdtype.h"

/**
 * ATA PIO logical block address read
 * 
 */
void read_sectors(void *ptr, uint32_t logical_block_address, uint8_t sector_count);

void write_sectors(void *ptr, uint32_t logical_block_address, uint8_t sector_count);

#endif