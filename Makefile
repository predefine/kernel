KERNEL := build/kernel.bin
INITRD := build/initrd.tar
INITRD_FILES := initrd/myfile.txt

OBJECTS := $(patsubst src/%.s,build/%.o,$(patsubst src/%.c,build/%.o,$(shell find src -type f)))

ALWAYS_REBUILD = $(wildcard *.h)

LINKER_SCRIPT := linker.ld

CFLAGS := -m32 -ffreestanding -O2 -Wall -Wextra -std=gnu99 -Iinclude
LDFLAGS := -T $(LINKER_SCRIPT) -nostdlib -z noexecstack

all: $(KERNEL)

test: $(KERNEL) $(INITRD)
	qemu-system-i386 -kernel $(KERNEL) -append "HI" -initrd $(INITRD)

# Todo
$(INITRD): $(INITRD_FILES)
	tar cvf $@ $^

$(KERNEL): $(OBJECTS) $(LINKER_SCRIPT) $(ALWAYS_REBUILD)
	$(CC) -o $@ $(OBJECTS) $(CFLAGS) $(LDFLAGS)

build/%.o: src/%.c $(ALWAYS_REBUILD)
	$(CC) -o $@ $< -c $(CFLAGS)

build/%.o: src/%.s
	$(AS) --32 -o $@ $<

clean:
	rm -f $(OBJECTS) $(KERNEL) $(INITRD)
