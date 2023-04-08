#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

#include "lib-header/stdtype.h"

#define MEMORY_FRAMEBUFFER     (uint8_t *) 0xC00B8000
#define CURSOR_PORT_CMD        0x03D4
#define CURSOR_PORT_DATA       0x03D5
#define FRAMEBUFFER_RESOLUTION (80*25)


/**
 * Terminal framebuffer
 * Resolution: 80x25
 * Starting at MEMORY_FRAMEBUFFER,
 * - Even number memory: Character, 8-bit
 * - Odd number memory:  Character color lower 4-bit, Background color upper 4-bit
*/

/**
 * Set framebuffer character and color with corresponding parameter values.
 * More details: https://en.wikipedia.org/wiki/BIOS_color_attributes
 *
 * @param row Vertical location (index start 0)
 * @param col Horizontal location (index start 0)
 * @param c   Character
 * @param fg  Foreground / Character color
 * @param bg  Background color
 */
void framebuffer_write(uint8_t row, uint8_t col, char c, uint8_t fg, uint8_t bg);

/**
 * Set cursor to specified location. Row and column starts from 0
 * 
 * @param r row
 * @param c column
*/
void framebuffer_set_cursor(uint8_t r, uint8_t c);

/**
 * Get cursor location. Divide with 80 for row and use modulo for column
 * 
 * @return uint16_t, position = y*80 + x
*/
uint16_t framebuffer_get_cursor(void);

/** 
 * Set all cell in framebuffer character to 0x00 (empty character)
 * and color to 0x07 (gray character & black background)
 * 
 */
void framebuffer_clear(void);

#endif