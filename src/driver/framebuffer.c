#include "lib-header/cpu/portio.h"
#include "lib-header/driver/framebuffer.h"
#include "lib-header/driver/vga.h"
#include "lib-header/stdtype.h"
#include "lib-header/stdmem.h"

enum cursor_command {
    UpperByte = 14u,
    LowerByte = 15u,
};

// TODO : Fancy text for mode 13h

void framebuffer_text_set_cursor(uint8_t r, uint8_t c) {
    if (_vga_current_video_mode == 3) {
        uint16_t location = (r * 0x50 + c) % MODE_3H_RESOLUTION;
        out(CURSOR_PORT_CMD, UpperByte);
        out(CURSOR_PORT_DATA, (location & 0xFF00u) >> 8);
        out(CURSOR_PORT_CMD, LowerByte);
        out(CURSOR_PORT_DATA, location & 0x00FFu);
    }
}

uint16_t framebuffer_text_get_cursor(void) {
    if (_vga_current_video_mode == 3) {
        uint16_t position = 0;
        out(CURSOR_PORT_CMD, LowerByte);
        position |= in(CURSOR_PORT_DATA);
        out(CURSOR_PORT_CMD, UpperByte);
        position |= ((uint16_t) in(CURSOR_PORT_DATA)) << 8;
        return position;
    }
    return -1;
}

void framebuffer_text_write(uint8_t row, uint8_t col, char c, uint8_t fg, uint8_t bg) {
    if (_vga_current_video_mode == 3) {
        uint8_t  back_color = (bg & 0xF) << 4;
        uint8_t  char_color = (fg & 0xF);
        uint16_t offset     = 2*(80*row + col);
        memset(MODE_3H_MEMORY_FRAMEBUFFER + offset, c, 1);
        memset(MODE_3H_MEMORY_FRAMEBUFFER + offset + 1, back_color | char_color, 1);
    }
}

void framebuffer_clear(void) {
    if (_vga_current_video_mode == 3) {
        for (size_t i = 0; i < 80; i++) {
            for (size_t j = 0; j < 25; j++) {
                memset(MODE_3H_MEMORY_FRAMEBUFFER + 2*(i+80*j) + 0,  ' ', 1);
                memset(MODE_3H_MEMORY_FRAMEBUFFER + 2*(i+80*j) + 1, 0x0F, 1);
            }
        }
        framebuffer_text_set_cursor(0, 0);
    }
    else if (_vga_current_video_mode == 0x13) {
        for (size_t i = 0; i < 320; i++)
            for (size_t j = 0; j < 200; j++)
                memset(MODE_13H_MEMORY_FRAMEBUFFER + i + 320*j, 0, 1);
    }
}