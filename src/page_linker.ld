ENTRY(loader)                /* the name of the entry label */

/* relocation on address at 0xC001 0000, but load address (physical location) still at 0x100000 */
SECTIONS {
    . = 0xC0100000;          /* link at 1MB */

    .multiboot ALIGN (0x1000) : AT (ADDR (.multiboot) - 0xC0000000)
    {
        *(.multiboot)        /* put GRUB multiboot header at front */
    }

    .setup.text ALIGN (0x1000) : AT (ADDR (.setup.text) - 0xC0000000)
    {
        *(.setup.text)       /* initial setup code */
    }

    .text ALIGN (0x1000) : AT (ADDR (.text) - 0xC0000000)
    {
        *(.text)             /* all text sections from all files */
    }

    .rodata ALIGN (0x1000) : AT (ADDR (.rodata) - 0xC0000000)
    {
        *(.rodata*)          /* all read-only data sections from all files */
    }

    .data ALIGN (0x1000) : AT (ADDR (.data) - 0xC0000000)
    {
        *(.data)             /* all data sections from all files */
    }

    .bss ALIGN (0x1000) : AT (ADDR (.bss) - 0xC0000000)
    {
        *(COMMON)            /* all COMMON sections from all files */
        *(.bss)              /* all bss sections from all files */
    }
}