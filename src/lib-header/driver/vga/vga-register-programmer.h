#ifndef _VGA_REGISTER_PROGRAMMER_H
#define _VGA_REGISTER_PROGRAMMER_H

#include "lib-header/stdtype.h"

// Note : Naming convention directly follow from http://www.osdever.net/FreeVGA/vga/vga.htm

// TODO : VGA Doxygen
// TODO : Second pass + formatting

struct VGARegisterPort {
    uint16_t   address_register;
    uint16_t   data_register;
} __attribute__((packed));

uint8_t register_const_serialize(const void *struct_ptr);
uint8_t vga_read_single_port_register(struct VGARegisterPort vga_reg);
void vga_set_single_port_register(struct VGARegisterPort vga_reg, uint8_t data);
void vga_set_double_port_register(struct VGARegisterPort vga_reg, uint8_t index, uint8_t data);
void set_indexed_register(struct VGARegisterPort vga_reg, uint8_t *indexes, uint8_t *datas, uint32_t count);

#endif