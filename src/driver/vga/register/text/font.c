#include "lib-header/driver/vga/video-mode-preset/vga-video-preset.h"
#include "lib-header/driver/vga/register/text/font.h"
#include "lib-header/driver/vga/register/text/bubach-font8x16.h"
#include "lib-header/driver/vga/register/graphics.h"
#include "lib-header/driver/vga/register/sequencer.h"
#include "lib-header/stdmem.h"

void vga_load_standard_vga_font(void) {
    // Need to change register to access font plane (plane number 2)
    // Graphics register
    uint8_t graphics_register = vga_read_double_port_register(_vga_reg_port_graphics, GRAPHICS_INDEX_GRAPHICS_MODE);
    uint8_t misc_register     = vga_read_double_port_register(_vga_reg_port_graphics, GRAPHICS_INDEX_MISCELLANEOUS_GRAPHICS);

    struct VGAGraphicsGraphicsModeData          temp_graphics_mode;
    struct VGAGraphicsMiscellaneousGraphicsData temp_misc_graphics;
    memcpy(&temp_graphics_mode, &graphics_register, 1);
    memcpy(&temp_misc_graphics, &misc_register, 1);
    temp_graphics_mode.write_mode        = 0;
    temp_graphics_mode.host_even_odd     = 0;
    temp_misc_graphics.chain_even_odd    = 0;
    temp_misc_graphics.memory_map_select = 1;
    vga_set_double_port_register(_vga_reg_port_graphics, GRAPHICS_INDEX_GRAPHICS_MODE, register_const_serialize(&temp_graphics_mode));
    vga_set_double_port_register(_vga_reg_port_graphics, GRAPHICS_INDEX_MISCELLANEOUS_GRAPHICS, register_const_serialize(&temp_misc_graphics));

    // Sequencer register
    uint8_t map_mask_register        = vga_read_double_port_register(_vga_reg_port_sequencer, SEQUENCER_INDEX_MAP_MASK);
    uint8_t memory_selector_register = vga_read_double_port_register(_vga_reg_port_sequencer, SEQUENCER_INDEX_MEMORY_MODE);

    struct VGASequencerMapMaskData    temp_map_mask    = { .enable_memory_plane_2 = 1 };
    struct VGASequencerMemoryModeData temp_memory_mode;
    memcpy(&temp_memory_mode, &memory_selector_register, 1);
    temp_memory_mode.disable_odd_even_memory = 1;
    vga_set_double_port_register(_vga_reg_port_sequencer, SEQUENCER_INDEX_MAP_MASK, register_const_serialize(&temp_map_mask));
    vga_set_double_port_register(_vga_reg_port_sequencer, SEQUENCER_INDEX_MEMORY_MODE, register_const_serialize(&temp_memory_mode));

    // Copying font
    uint32_t font_address = VGA_LOWEST_FRAMEBUFFER_ADDRESS;
    for (uint32_t i = 0; i < 256; i++) {
        memcpy((void*) font_address, bubach_font_8x16 + i*16, 16);
        font_address += 32; // Due every char is 32 bytes (first 16 bytes is bitmap), we need to jump per 32 bytes
    }

    // Restore original register
    vga_set_double_port_register(_vga_reg_port_graphics, GRAPHICS_INDEX_GRAPHICS_MODE, graphics_register);
    vga_set_double_port_register(_vga_reg_port_graphics, GRAPHICS_INDEX_MISCELLANEOUS_GRAPHICS, misc_register);

    vga_set_double_port_register(_vga_reg_port_sequencer, SEQUENCER_INDEX_MAP_MASK, map_mask_register);
    vga_set_double_port_register(_vga_reg_port_sequencer, SEQUENCER_INDEX_MEMORY_MODE, memory_selector_register);
}