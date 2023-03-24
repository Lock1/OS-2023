#include "lib-header/textio.h"
#include "lib-header/framebuffer.h"

void puts(char *buf, int32_t count, uint8_t color) {
    uint16_t cursor_location = framebuffer_get_cursor();
    uint8_t row = cursor_location / 80;
    uint8_t col = cursor_location % 80;
    int i = 0;
    while (i < count && buf[i] != '\0') {
        if (buf[i] == '\n') {
            row++;
            col = 0;
        } else {
            framebuffer_write(row, col++, buf[i], color, 0);
        }
        i++;
    }
    framebuffer_set_cursor(row, col);
}