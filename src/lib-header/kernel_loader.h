#ifndef _KERNEL_LOADER
#define _KERNEL_LOADER

/**
 * Load GDT from gdt_descriptor and launch protected mode
 * 
 * @param gdt_descriptor Pointer to already defined & initialized GDTDescriptor
 */
extern void launch_protected_mode(struct GDTDescriptor *gdt_descriptor);

#endif