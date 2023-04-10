#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

#include "lib-header/stdtype.h"

#define CURSOR_PORT_CMD        0x03D4
#define CURSOR_PORT_DATA       0x03D5


// TODO : Need to recheck all framebuffer doxygen & add more
void framebuffer_graphic_put_pixel(uint32_t x, uint32_t y, uint8_t color);

// FIXME : Temporary and quick solution
void framebuffer_draw_sis_image(void *buffer, uint32_t res_x, uint32_t res_y);
void framebuffer_draw_256_color_palette(void);


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
void framebuffer_text_write(uint8_t row, uint8_t col, char c, uint8_t fg, uint8_t bg);

/**
 * Set cursor to specified location. Row and column starts from 0
 * 
 * @param r row
 * @param c column
*/
void framebuffer_text_set_cursor(uint8_t r, uint8_t c);

/**
 * Get cursor location. Divide with 80 for row and use modulo for column
 * 
 * @return uint16_t, position = y*80 + x
*/
uint16_t framebuffer_text_get_cursor(void);

/** 
 * For text mode:
 * Set all cell in framebuffer character to 0x00 (empty character)
 * and color to 0x07 (gray character & black background)
 * 
 * For graphical mode:
 * Set all pixel to black
 */
void framebuffer_clear(void);

#endif