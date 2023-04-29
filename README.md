# OS 2023
Repository untuk testing spesifikasi IF2230 Sistem Operasi ITB 2023

Mengambil beberapa ide utama dari [littleosbook - Erik Helin, Adam Renberg](https://littleosbook.github.io/), [tugas besar OS-2022](https://github.com/Sister19/OS-2022), dan [pengerjaan OS sebelumnya](https://github.com/Lock1/IF2230-OS). Dibuat sepenuhnya dari scratch dan diadjust untuk keperluan tugas besar IF2230. Kit dan spesifikasi pengerjaan dapat diakses pada [Sister20/kit-OS-2023](https://github.com/Sister20/kit-OS-2023)

---

*Mock-up* shell (yang ada pada spesifikasi)

![Shell sample](other/img/shell-sample.gif)


Karena ada sedikit masalah dengan directory name length dengan manim (temporary file biasanya relatif panjang filenamenya), untuk source code animasi manim dipindah ke separate repository:

https://github.com/Lock1/OS-2023-Manim

[Dev Repository untuk kit](https://github.com/Lock1/kit-OS-2023)


## Coding Convention
- Yes, insane verbosity, but i like it anyway
- 0 `typedef` use for `struct` (except function pointer and pointer mumbo jumbo if needed)
- Global variable use `_<filename>_<variable name>`
- Assembly filename: `<filename>-asm.s`, with `filename` is same with C counterpart (ex. `interrupt.c` and `interrupt-asm.s`)
- Both `<filename>-asm.s` and `<filename>.c` will use single header `<filename>.h`
- Special exception for `kernel.c` and `kernel-entrypoint.s`, with single header `kernel.h`



## Planned Roadmap
### Milestone 1
1-5
- [x] Initial setup & toolchain install
- [x] Bootloader
- [x] I/O Memory Map (VGA)
- [x] Global Descriptor Table (GDT) + Protected Mode
- [x] Initial kit / template milestone 1


### Milestone 2
6-11
- [x] Interrupt (IRQ kaya keyboard)
- [x] Filesystem
- [ ] ~~Basic process + monotasking~~ Dropped for milestone 2

### Milestone 3
12-End
- [x] Paging
- [x] User mode
- [x] Basic shell


### Dropped
Seems too hard?
- [ ] ~~Memory management (memcpy, malloc, etc)~~
- [ ] ~~Multitasking~~


## Resources
- Most of the main idea : https://littleosbook.github.io/
- Bootloader & GRUB : http://www.jamesmolloy.co.uk/tutorial_html/index.html + https://littleosbook.github.io/



Other reference
- https://539kernel.com/
- https://github.com/tuhdo/os01
- https://github.com/HazemGabr232/Simple_OS
- http://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
- https://wiki.osdev.org/Expanded_Main_Page
- https://github.com/cfenollosa/os-tutorial
