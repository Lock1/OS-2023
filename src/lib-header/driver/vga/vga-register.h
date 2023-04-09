#ifndef _VGA_REGISTER_H
#define _VGA_REGISTER_H

#include "lib-header/stdtype.h"

// Note : Naming convention directly follow from http://www.osdever.net/FreeVGA/vga/vga.htm

// TODO : VGA Doxygen

// TODO : Second pass + formatting
// External & Attribute is unindexed
// TODO : Rename indexed -> single port / multi
// TODO : Rename this to vga-register-programming

// VGA Register: avoiding raw bytes and use struct as much as possible, even if somewhat feel stupid
struct VGARegisterPort {
    uint16_t   address_register;
    uint16_t   data_register;
} __attribute__((packed));

uint8_t register_const_serialize(const void *struct_ptr);
uint8_t vga_read_unindexed_register(struct VGARegisterPort vga_reg);
void vga_set_unindexed_register(struct VGARegisterPort vga_reg, uint8_t data);
void vga_set_index_register(struct VGARegisterPort vga_reg, uint8_t index, uint8_t data);
void set_indexed_register(struct VGARegisterPort vga_reg, uint8_t *indexes, uint8_t *datas, uint32_t count);

#endif