# Milestone 1
[Link to milestone 1 document](https://docs.google.com/document/d/1ebhX-D_bNafray9C6T8cmgAy8_E58i_uWkngrNWHjr4/edit#)

## 0. Toolchains & dependencies
- qemu -> Main execution environment
- gcc  -> Main compiler, bonus bisa inline asm
- nasm -> Optional asm compiler (?)
- GRUB -> Bootloader
- make -> Build system


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

## 2. Bootloader
Source
1. http://www.jamesmolloy.co.uk/tutorial_html/index.html
2. https://littleosbook.github.io/
**WIP, Grub QEMU**

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

## 3. Global Descriptor Table (GDT) + Protected Mode
WIP


## 4. I/O Memory Map (VGA)
WIP
