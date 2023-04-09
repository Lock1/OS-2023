#ifndef _VGA_H
#define _VGA_H

#include "lib-header/stdtype.h"
#include "lib-header/driver/vga/video-mode-preset/vga-video-preset.h"

/** 
 * Change VGA video mode to 13h
 * Video mode 13h - 320x200 - 256 Colors - Graphical mode
 * Heavily inspired by http://bos.asmhackers.net/docs/vga_without_bios/snippet_5/vga.php
 * Completely written in C and using http://www.osdever.net/FreeVGA/vga/vga.htm as reference sheet
*/
void vga_use_video_mode_13h(void);

/**
 * Terminal framebuffer
 * Resolution: 80x25
 * Starting at MEMORY_FRAMEBUFFER,
 * - Even number memory: Character, 8-bit
 * - Odd number memory:  Character color lower 4-bit, Background color upper 4-bit
*/
// TODO : Switch back to mode 3
// TODO : Currently only assuming color mode, all port is written like that (all port shifted)

// By default GRUB use video mode 3 (text mode, 80x25)
extern uint8_t _vga_current_video_mode;

#endif