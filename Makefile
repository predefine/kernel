KERNEL := kernel.bin
KERNEL_OBJECTS := kernel.o io.o idt.o asm.o pic.o
OBJECTS := main.o $(KERNEL_OBJECTS)

all: $(KERNEL)

test: $(KERNEL)
	qemu-system-i386 -kernel $(KERNEL) -d int

$(KERNEL): $(OBJECTS) linker.ld
	$(CC) -T linker.ld -m32 -o $@ -ffreestanding -O2 -nostdlib -lgcc -z noexecstack $(OBJECTS)

%.o: %.c
	$(CC) -o $@ $< -m32 -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I.

%.o: %.s
	$(AS) --32 -o $@ $<

clean:
	rm -f $(OBJECTS) $(KERNEL)
