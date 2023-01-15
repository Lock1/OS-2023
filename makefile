ASM = nasm
LINKER = ld
SOURCE_FOLDER = src
OUTPUT_FOLDER = bin

build: $(BOOTSTRAP_FILE) $(KERNEL_FILE)
	$(ASM) -f elf32 $(SOURCE_FOLDER)/loader.s -o $(OUTPUT_FOLDER)/loader.o
	$(LINKER) -T $(SOURCE_FOLDER)/linker.ld -melf_i386 $(OUTPUT_FOLDER)/loader.o -o $(OUTPUT_FOLDER)/kernel
	mkdir -p $(OUTPUT_FOLDER)/iso/boot/grub
	
	qemu-system-x86_64 -s $(OUTPUT_FOLDER)/kernel.img

clean:
	rm -f *.o