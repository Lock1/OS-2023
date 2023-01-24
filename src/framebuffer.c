#include "lib-header/framebuffer.h"
#include "lib-header/stdtype.h"
#include "lib-header/memory.h"
#include "lib-header/portio.h"

enum cursor_command {
    UpperByte = 14u,
    LowerByte = 15u,
};

void framebuffer_set_cursor(uint8_t r, uint8_t c) {
    uint16_t location = r * 0x50 + c;
    out(CURSOR_PORT_CMD, UpperByte);
    out(CURSOR_PORT_DATA, location & 0xFF00u);
    out(CURSOR_PORT_CMD, LowerByte);
    out(CURSOR_PORT_DATA, location & 0x00FFu);
}

void framebuffer_write(uint16_t i, char c, uint8_t fg, uint8_t bg) {
    uint8_t high = (fg & 0xF) << 4;
    uint8_t low  = (bg & 0xF);
    memset(MEMORY_FRAMEBUFFER + i, c, 1);
    memset(MEMORY_FRAMEBUFFER + i + 1, high | low, 1);
}