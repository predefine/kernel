KERNEL := kernel.bin
INITRD := initrd.tar
INITRD_FILES := myfile.txt pic.c stdio.h
KERNEL_OBJECTS := kernel.o stdio.o idt.o asm.o pic.o tar.o
OBJECTS := main.o $(KERNEL_OBJECTS)

ALWAYS_REBUILD = $(wildcard *.h)

all: $(KERNEL)

test: $(KERNEL) $(INITRD)
	qemu-system-i386 -kernel $(KERNEL) -append "HI" -initrd $(INITRD)

# Todo
$(INITRD): $(INITRD_FILES)
	tar cvf $@ $^

$(KERNEL): $(OBJECTS) linker.ld $(ALWAYS_REBUILD)
	$(CC) -T linker.ld -m32 -o $@ -ffreestanding -O2 -nostdlib -z noexecstack $(OBJECTS)

%.o: %.c $(ALWAYS_REBUILD)
	$(CC) -o $@ $< -m32 -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I.

%.o: %.s
	$(AS) --32 -o $@ $<

clean:
	rm -f $(OBJECTS) $(KERNEL) $(INITRD)
