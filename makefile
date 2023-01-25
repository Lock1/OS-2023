ASM = nasm -f elf32
CC = gcc -m32 -c -ffreestanding -fno-stack-protector -fno-pie -fno-asynchronous-unwind-tables -nostartfiles -Wall -Wextra -Werror
LINKER = ld -Tlinker.ld -melf_i386
SOURCE_FOLDER = src
OUTPUT_FOLDER = bin
FINAL_IMAGE = os.iso

kernel:
	$(ASM) $(SOURCE_FOLDER)/loader.asm
	$(CC) $(SOURCE_FOLDER)/kernel.c -o $(SOURCE_FOLDER)/kernel.o
	$(LINKER) $(SOURCE_FOLDER)/loader.o $(SOURCE_FOLDER)/kernel.o -o $(OUTPUT_FOLDER)/boot/kernel.o

kernel-debug:
	$(ASM) $(SOURCE_FOLDER)/loader.asm -g -F dwarf
	$(CC) $(SOURCE_FOLDER)/kernel.c -o $(SOURCE_FOLDER)/kernel.o -g
	$(LINKER) $(SOURCE_FOLDER)/loader.o $(SOURCE_FOLDER)/kernel.o -o $(OUTPUT_FOLDER)/boot/kernel.o -g

build:
	genisoimage -R                              \
				-b boot/grub/grub               \
				-no-emul-boot                   \
				-boot-load-size 4               \
				-A os                           \
				-input-charset utf8             \
				-quiet                          \
				-boot-info-table                \
				-o $(FINAL_IMAGE)               \
				$(OUTPUT_FOLDER)

run: kernel build
	qemu-system-i386 -boot d -cdrom os.iso

debug: kernel-debug build
	qemu-system-i386 -boot d -cdrom os.iso -s -S -daemonize
