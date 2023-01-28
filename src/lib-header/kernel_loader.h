#ifndef _KERNEL_LOADER
#define _KERNEL_LOADER

/**
 * Load GDT from gdt_descriptor and launch protected mode. This function defined in asm source code.
 * 
 * @param gdt_descriptor Pointer to already defined & initialized GDTDescriptor
 * @warning Invalid address / definition of GDT will cause bootloop after calling this function.
 */
extern void launch_protected_mode(struct GDTDescriptor *gdt_descriptor);

#endif