ASM = nasm
SOURCE_FOLDER = src
OUTPUT_FOLDER = bin
BOOTSTRAP_FILE = $(SOURCE_FOLDER)/bootstrap.asm 
KERNEL_FILE = $(SOURCE_FOLDER)/simple_kernel.asm

build: $(BOOTSTRAP_FILE) $(KERNEL_FILE)
	$(ASM) -f bin $(BOOTSTRAP_FILE) -o $(OUTPUT_FOLDER)/bootstrap.o
	$(ASM) -f bin $(KERNEL_FILE) -o $(OUTPUT_FOLDER)/kernel.o
	dd if=$(OUTPUT_FOLDER)/bootstrap.o of=$(OUTPUT_FOLDER)/kernel.img
	dd seek=1 conv=sync if=$(OUTPUT_FOLDER)/kernel.o of=$(OUTPUT_FOLDER)/kernel.img bs=512
	qemu-system-x86_64 -s $(OUTPUT_FOLDER)/kernel.img

clean:
	rm -f *.o