# Object files & root temporaty folder
OBJECTS = kernel-entrypoint.o kernel.o \
	generic-lib/stdmem.o \
	driver/framebuffer.o driver/keyboard.o driver/disk.o driver/vga.o \
	cpu/portio.o cpu/gdt.o cpu/idt.o cpu/interrupt.o cpu/interrupt-asm.o \
	filesystem/fat32.o \
	memory/paging.o \
	driver/text-io-module/textio.o \
	driver/vga/vga-register.o \
	driver/vga/register/sequencer.o driver/vga/register/crt-controller.o driver/vga/register/external.o \
	driver/vga/register/graphics.o driver/vga/register/attribute-controller.o driver/vga/register/color.o
FOLDERS = cpu memory driver filesystem generic-lib

# Compiler & linker
ASM = nasm
LIN = ld
CC  = gcc

# Directory
SOURCE_FOLDER = src
OUTPUT_FOLDER = bin
ISO_NAME      = os2023
DISK_NAME     = storage
VPATH         = $(SOURCE_FOLDER)

# Flags
WARNING_CFLAG = -Wall -Wextra -Werror
DEBUG_CFLAG   = -ffreestanding -fshort-wchar -g
STRIP_CFLAG   = -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs
CFLAGS        = $(DEBUG_CFLAG) $(WARNING_CFLAG) $(STRIP_CFLAG) -m32 -c -I$(SOURCE_FOLDER)
AFLAGS        = -f elf32 -g -F dwarf
LFLAGS        = -T $(SOURCE_FOLDER)/external-linker-iso/linker.ld -melf_i386


run: all
	@qemu-system-i386 -s -S -drive file=$(OUTPUT_FOLDER)/$(DISK_NAME).bin,format=raw,if=ide,index=0,media=disk -cdrom $(ISO_NAME).iso 
all: build
build: iso
clean: delete-temp
	rm -rf *.o *.iso bin/kernel

delete-temp:
	@rm -f *.o
	for folder in $(FOLDERS) ; do rm -rf $$folder ; done



disk:
	@qemu-img create -f raw $(OUTPUT_FOLDER)/$(DISK_NAME).bin 4M

inserter:
	@$(CC) -Wno-builtin-declaration-mismatch -g -I$(SOURCE_FOLDER) \
		$(SOURCE_FOLDER)/generic-lib/stdmem.c $(SOURCE_FOLDER)/filesystem/fat32.c \
		$(SOURCE_FOLDER)/external-program/external-inserter.c \
		-o $(OUTPUT_FOLDER)/inserter

user-shell:
	@$(ASM) $(AFLAGS) $(SOURCE_FOLDER)/external-program/user-entry.s -o user-entry.o
	@$(CC)  $(CFLAGS) -fno-pie $(SOURCE_FOLDER)/external-program/user-shell.c -o user-shell.o
	@$(LIN) -T $(SOURCE_FOLDER)/external-program/user-linker.ld -melf_i386 \
		user-entry.o user-shell.o -o $(OUTPUT_FOLDER)/shell
	@echo Linking object shell object files and generate flat binary...
	@$(LIN) -T $(SOURCE_FOLDER)/external-program/user-linker.ld -melf_i386 --oformat=elf32-i386\
		user-entry.o user-shell.o -o $(OUTPUT_FOLDER)/shell_elf
	@echo Linking object shell object files and generate ELF32 for debugging...
	@size --target=binary bin/shell
	@rm -f *.o

insert-shell: inserter user-shell
	@echo Inserting shell into root directory...
	@cd bin; ./inserter shell 2 $(DISK_NAME).bin
	@cd bin; ./inserter ikanaide 2 $(DISK_NAME).bin

kernel: $(OBJECTS)
	@$(LIN) $(LFLAGS) $(OBJECTS) -o $(OUTPUT_FOLDER)/kernel
	@echo Linking object files and generate elf32...
	@$(MAKE) delete-temp

iso: kernel
	@mkdir -p $(OUTPUT_FOLDER)/iso/boot/grub
	@cp $(OUTPUT_FOLDER)/kernel     $(OUTPUT_FOLDER)/iso/boot/
	@cp other/grub1_stage2_eltorito $(OUTPUT_FOLDER)/iso/boot/grub/
	@cp $(SOURCE_FOLDER)/external-linker-iso/menu.lst $(OUTPUT_FOLDER)/iso/boot/grub/
	@genisoimage -R                          \
		-b boot/grub/grub1_stage2_eltorito  \
		-no-emul-boot                       \
		-boot-load-size 4                   \
		-A os                               \
		-input-charset utf8                 \
		-quiet                              \
		-boot-info-table                    \
		-o $(OUTPUT_FOLDER)/$(ISO_NAME).iso \
		$(OUTPUT_FOLDER)/iso
	@rm -r $(OUTPUT_FOLDER)/iso/

%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $< -o $@
	@echo Compiling $@...

%.o: %.s
	@mkdir -p $(@D)
	@$(ASM) $(AFLAGS) $< -o $@
	@echo Compiling $@...