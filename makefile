# Object files
OBJECTS = kernel.o kernel_loader.o portio.o stdmem.o framebuffer.o gdt.o idt.o interrupt.o intsetup.o

# Compiler & linker
ASM = nasm
LIN = ld
CC  = gcc

# Directory
SOURCE_FOLDER = src
OUTPUT_FOLDER = bin
ISO_NAME      = os2023

# Flags
WARNING_CFLAG = -Wall -Wextra -Werror
DEBUG_CFLAG   = -ffreestanding -fshort-wchar -g
STRIP_CFLAG   = -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs
CFLAGS        = $(DEBUG_CFLAG) $(WARNING_CFLAG) $(STRIP_CFLAG) -m32 -c -I$(SOURCE_FOLDER)
AFLAGS        = -f elf32 -g -F dwarf
LFLAGS        = -T $(SOURCE_FOLDER)/linker.ld -melf_i386


run: all
	@qemu-system-i386 -s -S -cdrom bin/$(ISO_NAME).iso
all: build
build: iso
clean:
	rm -rf *.o *.iso bin/kernel



kernel: $(OBJECTS)
	@$(LIN) $(LFLAGS) $(OBJECTS) -o $(OUTPUT_FOLDER)/kernel
	@echo Linking object files and generate elf32...
	@rm -f *.o

iso: kernel
	@mkdir -p $(OUTPUT_FOLDER)/iso/boot/grub
	@cp $(OUTPUT_FOLDER)/kernel     $(OUTPUT_FOLDER)/iso/boot/
	@cp other/grub1_stage2_eltorito $(OUTPUT_FOLDER)/iso/boot/grub/
	@cp $(SOURCE_FOLDER)/menu.lst   $(OUTPUT_FOLDER)/iso/boot/grub/
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

%.o: $(SOURCE_FOLDER)/%.c
	@$(CC)  $(CFLAGS) $< -o $@
	@echo Compiling $@...

%.o: $(SOURCE_FOLDER)/%.s
	@$(ASM) $(AFLAGS) $< -o $@
	@echo Compiling $@...