ASM           = nasm
LINKER        = ld
SOURCE_FOLDER = src
OUTPUT_FOLDER = bin
CFLAGS        = -ffreestanding -fshort-wchar -g -m32
ISO_NAME      = os2023

build: iso

kernel:
	$(ASM) -g -f elf32 $(SOURCE_FOLDER)/loader.s -o $(OUTPUT_FOLDER)/loader.o
	$(LINKER) -T $(SOURCE_FOLDER)/linker.ld -melf_i386 $(OUTPUT_FOLDER)/loader.o -o $(OUTPUT_FOLDER)/kernel

iso: kernel
	mkdir -p $(OUTPUT_FOLDER)/iso/boot/grub
	cp $(OUTPUT_FOLDER)/kernel $(OUTPUT_FOLDER)/iso/boot/
	cp other/grub1_stage2_eltorito $(OUTPUT_FOLDER)/iso/boot/grub/
	cp $(SOURCE_FOLDER)/menu.lst $(OUTPUT_FOLDER)/iso/boot/grub/
	genisoimage -R                          \
		-b boot/grub/grub1_stage2_eltorito  \
		-no-emul-boot                       \
		-boot-load-size 4                   \
		-A os                               \
		-input-charset utf8                 \
		-quiet                              \
		-boot-info-table                    \
		-o $(OUTPUT_FOLDER)/$(ISO_NAME).iso \
		$(OUTPUT_FOLDER)/iso

clean:
	rm -f *.o