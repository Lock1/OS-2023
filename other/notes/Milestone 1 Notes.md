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
`qemu-system-x86_64 -s -cdrom bin/os2023.iso`

Debugger
Open WSL in root and type `code .`
`-exec` prefix for gdb command in VSCode Debug Console
Example: `-exec set $rax=5`

Note with watchpoint: `int` will be treated as such, signed integer,
be careful with expression `a > 0` or `a < 0`. Make sure to remember variable type declaration.

`F5` to start debugging
`Shift + F5` to stop debugging

Right click at call stack to see assembly form
![VSCode asm](/other/img/disassembly.jpg)


## 3. I/O Memory Map (VGA)
`gcc` guidelines
1. Any struct will use `__attribute__((packed))`
```c
struct example {
    unsigned char config;   /* bit 0 - 7   */
    unsigned short address; /* bit 8 - 23  */
    unsigned char index;    /* bit 24 - 31 */
} __attribute__((packed));
```
2. If needed, `gcc` inline asm can be useful (https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html)
3. Add comment like this, in order to add definition to Intellisense
```c
/** out:
 *  Sends the given data to the given I/O port
 *
 *  @param port The I/O port to send the data to
 *  @param data The data to send to the I/O port
 */
void out(unsigned short port, unsigned char data);
```


This section will create "driver" for the screen. 
- The screen is text mode with resolution 80x25 character
- Controlling the screen require
    - Memory-mapped I/O filled with framebuffer (in character), located at 0xB8000
    - I/O ports for controlling cursor, located at 0x3D4 and 0x3D5



## 4. Global Descriptor Table (GDT) + Protected Mode
WIP



