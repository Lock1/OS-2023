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
// Completely software acceleration
void framebuffer_graphic_put_pixel(uint32_t x, uint32_t y, uint8_t color) {
    uint8_t *addr = (uint8_t *) 0xC00A0000 + (320*y) + x;
    *addr = color;
}

void draw_8x8_box(uint32_t x, uint32_t y, uint8_t color) {
    for (uint32_t i = 0; i < 8; i++)
        for (uint32_t j = 0; j < 8; j++)
            framebuffer_graphic_put_pixel(x + i, y + j, color);
}

void framebuffer_draw_256_color_palette() {
    for (uint32_t i = 0; i < 16; i++)
        for (uint32_t j = 0; j < 16; j++)
            draw_8x8_box(j*8, i*8, i*16 + j);
}

void framebuffer_draw_sis_image(void *buffer, uint32_t res_x, uint32_t res_y) {
    vga_use_video_mode_13h();
    framebuffer_clear();
    uint8_t *image_ptr = (uint8_t*) buffer;

    // TODO : Theres still a lot to cleanup on OS side
    // FIXME : This res_x & y probably broken
    for (uint32_t i = 0; i < res_x; i++) {
        for (uint32_t j = 0; j < res_y; j++) {
            uint8_t color = image_ptr[j*320 + i];
            framebuffer_graphic_put_pixel(i, j, color);
        }
    }
}

void framebuffer_play_ter_video(void *buffer) {
    vga_use_video_mode_13h();
    framebuffer_clear();
    uint16_t *ter_buf = (uint16_t*) buffer;
    uint32_t current_pixel_count = 0;
    uint32_t current_frame       = 1;
    for (uint32_t i = 0; i < 100000; i++) {
        uint8_t color  = 0;
        if (ter_buf[i] & 0x80)
            color = 0x1F;
        uint16_t length = ter_buf[i] & 0x7F;
        current_pixel_count += length;
        for (uint32_t j = 0; j < length; j++) {
            uint32_t pos = current_pixel_count + j;
            framebuffer_graphic_put_pixel(pos % 320, pos / 320, color);
        }
        if (current_pixel_count > 64000) {
            current_pixel_count = 0;
            current_frame++;
        }
    }
}

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
        uint16_t offset     = (80*row + col) << 1;
        MODE_3H_MEMORY_FRAMEBUFFER[offset]   = c;
        MODE_3H_MEMORY_FRAMEBUFFER[offset+1] = back_color | char_color;
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