# Milestone 1
[Link to milestone 1 document](https://docs.google.com/document/d/1ebhX-D_bNafray9C6T8cmgAy8_E58i_uWkngrNWHjr4/edit#)


## 0. Toolchains & dependencies
- qemu        -> Main execution environment
- gcc         -> Main compiler, bonus bisa inline asm
- nasm        -> Optional asm compiler (?)
- GRUB        -> Bootloader
- make        -> Build system
- genisoimage -> Creating system image

- gdb    -> Debugger
- vscode -> Editor + Debugger integration

## 1. Initial setup & toolchain install
- Recommended Host : Ubuntu 20.04
- Untested : Any linux-based system

- gcc, nasm, make, qemu
- Optional: gdb

`sudo apt-get update`
`sudo apt-get install gcc nasm make qemu genisoimage`

Recommended
`sudo apt-get install gdb`
Main editor: Visual Studio Code
`winget install microsoft.visualstudiocode` For Windows
`code --install-extension ms-vscode.cpptools`
`code --install-extension ms-vscode-remote.remote-wsl`

## 2. Bootloader
Source
1. http://www.jamesmolloy.co.uk/tutorial_html/index.html
2. https://littleosbook.github.io/
3. https://wiki.osdev.org/Meaty_Skeleton

Note : Win10 WSL still need to manual install xserver, refer to this repo: https://github.com/Sister19/WSL-Troubleshoot 

Debugger : https://www.youtube.com/watch?v=XLw_K4rEl1I 

- `menu.lst` GRUB configuration
- `linker.ld` Linker configuration for kernel
- `loader.s` Main kernel so far, just basically nothing except change `$eax` to `0xCAFEBABE`

Currently not used
- `kernel.c` for later purpose, still not used
- `bootstrap.asm` not from LittleOS
- `simple_kernel.asm` not from LittleOS

Running OS
`qemu-system-i386 -s -cdrom bin/os2023.iso`

Debugger
Open WSL in root and type `code .`
`-exec` prefix for gdb command in VSCode Debug Console
Example: `-exec set $rax=5`

By default, vscode configuration included is set to hexadecimal view

Note with watchpoint: `int` will be treated as such, signed integer,
be careful with expression `a > 0` or `a < 0`. Make sure to remember variable type declaration.

`F5` to start debugging
`Shift + F5` to stop debugging
`Ctrl + Shift + B` for build task

Right click at call stack to see assembly form
![VSCode asm](/other/img/disassembly.jpg)


## 3. I/O Memory Map (VGA)
`gcc` guidelines
0. Preface: This is kernel dev, no handholding, no memory safeguard, `gcc -Werror` is recommended. Disable `-Werror` only when debugging
1. Any struct will use `__attribute__((packed))`
```c
struct example {
    unsigned char config;   /* bit 0 - 7   */
    unsigned short address; /* bit 8 - 23  */
    unsigned char index;    /* bit 24 - 31 */
} __attribute__((packed));
```
2. If needed, `gcc` inline asm can be useful
    - https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html
    - https://wiki.osdev.org/Inline_Assembly/Examples
    - https://ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html#s3
    - https://dmalcolm.fedorapeople.org/gcc/2015-08-31/rst-experiment/how-to-use-inline-assembly-language-in-c-code.html#goto-labels
    - Usually "a" "b" "c" "d" constraint denote register `ax`, `bx`, `cx`, `dx`

3. Add comment like this (Doxygen format https://devblogs.microsoft.com/cppblog/visual-studio-code-c-extension-july-2020-update-doxygen-comments-and-logpoints/), in order to add definition to Intellisense
```c
/** out:
 *  Sends the given data to the given I/O port
 *
 *  @param port The I/O port to send the data to
 *  @param data The data to send to the I/O port
 */
void out(unsigned short port, unsigned char data);
```

4. If really need some unused variable for very specific purpose, learn to use `volatile` keyword

This section will create "driver" for the screen. 
- The screen is text mode with resolution 80x25 character
- Controlling the screen require
    - Memory-mapped I/O filled with framebuffer (in character), located at 0xB8000
    - I/O ports for controlling cursor, located at 0x3D4 and 0x3D5

5. Even using gcc bitfield, total struct size still aligned to nearest upper (ceiled) 8-bit / 1 byte. This can be affect alignment sensitive struct such GDT

6. Use leading underscore and filename for global kernel variable (Ex. `_memory_gdtr`)


For main document : Show memory layout, from empty, loading kernel into memory, and continued

## 4. Global Descriptor Table (GDT) + Protected Mode
Main document : Describe & illustrate GDT, littleosbook does pretty good job describing them already
- https://wiki.osdev.org/Global_Descriptor_Table
- https://wiki.osdev.org/GDT_Tutorial
- https://wiki.osdev.org/Segment_Selector
- https://www.intel.com/content/www/us/en/architecture-and-technology/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.html.html
- http://www.osdever.net/bkerndev/Docs/gdt.htm
- Intel Manual 9.9.1. Switching to Protected Mode

Due very sensitive nature of GDT, in my opinion, best left only GDT definition to student. 
But also due integral nature of GDT in memory management, this section should force them to read manual.
We will provide `launch_protected_mode` declaration and definition, student instead should figure out to fill proper GDT according to Intel Manual / OSDev.
