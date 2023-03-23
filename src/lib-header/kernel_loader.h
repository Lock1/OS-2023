#ifndef _KERNEL_LOADER
#define _KERNEL_LOADER

/**
 * Load GDT from gdtr and launch protected mode. This function defined in asm source code.
 * 
 * @param gdtr Pointer to already defined & initialized GDTR
 * @warning Invalid address / definition of GDT will cause bootloop after calling this function.
 */
extern void enter_protected_mode(struct GDTR *gdtr);

/**
 * Execute user program from kernel. This function defined in asm source code.
 * 
 * @param virtual_addr Pointer into user program that already in memory
 * @warning            Assuming pointed memory is properly loaded
 */
extern void kernel_execute_user_program(void *virtual_addr);



#endif