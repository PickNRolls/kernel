ifneq ("$(wildcard .env)", "")
include .env
export
endif

C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

# Change this if your cross-compiler is somewhere else
ifeq ($(ON_MACBOOK), 1)
CC = i686-elf-gcc
GDB = i386-elf-gdb
LD = i686-elf-ld
else
CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
GDB = i386-elf-gdb
LD = i386-elf-ld
endif
# -g: Use debugging symbols in gcc
CFLAGS = -g -ffreestanding -Wall -Wextra -fno-exceptions -m32 

# First rule is run by default
os_image.bin: bootloader/bootloader.bin kernel.bin
	cat $^ > os_image.bin

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: bootloader/kernel_entry.o ${OBJ}
	${LD} -o $@ -T kernel.ld $^ --oformat binary

# Used for debugging purposes
kernel.elf: bootloader/kernel_entry.o ${OBJ}
	${LD} -o $@ -T kernel.ld $^ 

run: os_image.bin
	qemu-system-i386 -fda os_image.bin

# Open the connection to qemu and load our kernel-object file with symbols
debug: os_image.bin kernel.elf
	qemu-system-i386 -s -S -fda os_image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os_image.bin *.elf
	rm -rf kernel/*.o bootloader/*.bin drivers/*.o bootloader/*.o cpu/*.o
