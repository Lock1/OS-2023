#ifndef _VGA_H
#define _VGA_H

/** 
 * Change VGA video mode to 13h
 * Video mode 13h - 320x200 - 256 Colors - Graphical mode
 * Heavily inspired by http://bos.asmhackers.net/docs/vga_without_bios/snippet_5/vga.php
 * Completely written in C and using http://www.osdever.net/FreeVGA/vga/vga.htm as reference sheet
*/
void vga_use_video_mode_13h(void);

#endif