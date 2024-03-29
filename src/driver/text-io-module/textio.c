#include "lib-header/driver/text-io-module/textio.h"
#include "lib-header/driver/framebuffer.h"

void puts(char *buf, int32_t count, uint8_t color) {
    uint16_t cursor_location = framebuffer_text_get_cursor();
    uint8_t row = cursor_location / 80;
    uint8_t col = cursor_location % 80;
    int i = 0;
    while (i < count && buf[i] != '\0') {
        if (buf[i] == '\n') {
            row++;
            col = 0;
        } else if (0x1F < buf[i] && buf[i] < 0x7F) {
            framebuffer_text_write(row, col++, buf[i], color, 0); // Only printables
        }
        i++;
    }
    framebuffer_text_set_cursor(row, col);
}