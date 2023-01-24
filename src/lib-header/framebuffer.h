#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

#include "lib-header/stdtype.h"

#define MEMORY_FRAMEBUFFER (uint8_t *) 0xB8000
#define CURSOR_PORT_CMD    0x03D4
#define CURSOR_PORT_DATA   0x03D5

/**
 * Terminal framebuffer
 * Resolution: 80x25
 * Starting at MEMORY_FRAMEBUFFER,
 * - Even number memory: Character, 8-bit
 * - Odd number memory:  Foreground color upper 4-bit, Background color lower 4-bit
*/

/** framebuffer_write:
 * Set framebuffer character and color with corresponding parameter values
 * 
 * @param i  Location in the framebuffer
 * @param c  Character
 * @param fg Foreground color
 * @param bg Background color
*/
void framebuffer_write(uint16_t i, char c, uint8_t fg, uint8_t bg);

/** framebuffer_set_cursor:
 * Set cursor to specified location. Row and column starts from 0
 * 
 * @param r row
 * @param c column
*/
void framebuffer_set_cursor(uint8_t r, uint8_t c);

#endif