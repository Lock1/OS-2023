#include "lib-header/driver/vga/vga-register-programmer.h"
#include "lib-header/cpu/portio.h"

uint8_t register_const_serialize(const void *struct_ptr) {
    return *((uint8_t *) struct_ptr);
}

uint8_t vga_read_single_port_register(struct VGARegisterPort vga_reg) {
    return in(vga_reg.data_register);
}

uint8_t vga_read_double_port_register(struct VGARegisterPort vga_reg, uint8_t index) {
    out(vga_reg.address_register, index);
    return in(vga_reg.data_register);
}

void vga_set_single_port_register(struct VGARegisterPort vga_reg, uint8_t data) {
    out(vga_reg.data_register, data);
}

void vga_set_double_port_register(struct VGARegisterPort vga_reg, uint8_t index, uint8_t data) {
    out(vga_reg.address_register, index);
    out(vga_reg.data_register, data);
}

void set_indexed_register(struct VGARegisterPort vga_reg, uint8_t *indexes, uint8_t *datas, uint32_t count) {
    for (uint32_t i = 0; i < count; i++)
        vga_set_double_port_register(vga_reg, indexes[i], datas[i]);
}