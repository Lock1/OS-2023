#ifndef _TEXTIO_H
#define _TEXTIO_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Simply write null-terminated string to framebuffer at current position
 * 
 * @param buf   Pointer to null-terminated string buffer
 * @param count How many character count to write
 * @param color Text foreground color
 */
void puts(char *buf, int32_t count, uint8_t color);

#endif