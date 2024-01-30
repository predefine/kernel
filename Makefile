KERNEL := kernel.bin
KERNEL_OBJECTS := kernel.o io.o idt.o asm.o pic.o
OBJECTS := main.o $(KERNEL_OBJECTS)

ALWAYS_REBUILD = $(wildcard *.h)

all: $(KERNEL)

test: $(KERNEL)
	qemu-system-i386 -kernel $(KERNEL) -append "HI" -initrd initrd.tar

# Todo
initrd.tar:
	touch $@

$(KERNEL): $(OBJECTS) linker.ld $(ALWAYS_REBUILD)
	$(CC) -T linker.ld -m32 -o $@ -ffreestanding -O2 -nostdlib -lgcc -z noexecstack $(OBJECTS)

%.o: %.c $(ALWAYS_REBUILD)
	$(CC) -o $@ $< -m32 -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I.

%.o: %.s
	$(AS) --32 -o $@ $<

clean:
	rm -f $(OBJECTS) $(KERNEL)
