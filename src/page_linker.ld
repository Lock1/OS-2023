ENTRY(loader)                /* the name of the entry label */

SECTIONS {
    . = 0x00400000;          /* link at 4MB */

    _kernel_start = .;
    .multiboot ALIGN (4M) :
    {
        *(.multiboot)        /* put GRUB multiboot header at front */
    }

    .setup.text ALIGN (4M) :
    {
        *(.setup.text)       /* initial setup code */
    }

    /* relocation address at 0xC000 0000, but load address (physical location) still continuing at 0x400000 */
    . += 0xC0000000;
    .text ALIGN (4M) : AT (ADDR (.text) - 0xC0000000)
    {
        *(.text)             /* all text sections from all files */
    }

    .rodata ALIGN (4M) : AT (ADDR (.rodata) - 0xC0000000)
    {
        *(.rodata*)          /* all read-only data sections from all files */
    }

    .data ALIGN (4M) : AT (ADDR (.data) - 0xC0000000)
    {
        *(.data)             /* all data sections from all files */
    }

    .bss ALIGN (4M) : AT (ADDR (.bss) - 0xC0000000)
    {
        *(COMMON)            /* all COMMON sections from all files */
        *(.bss)              /* all bss sections from all files */
    }
    _kernel_end = .;
}