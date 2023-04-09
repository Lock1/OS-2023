#ifndef _VGA_FONT_REGISTER_H
#define _VGA_FONT_REGISTER_H

#include "lib-header/driver/vga/vga-register-programmer.h"
#include "lib-header/stdtype.h"

// https://wiki.osdev.org/VGA_Fonts
// http://bos.asmhackers.net/docs/vga_without_bios/snippet_5/vga.php
void vga_load_standard_vga_font(void);

#endif