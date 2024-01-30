#pragma once

#define MULTIBOOT_INFO_MEMORY 1
#define MULTIBOOT_INFO_BOOTDEV 1<<1
#define MULTIBOOT_INFO_CMDLINE 1<<2
#define MULTIBOOT_INFO_MODS 1<<3

#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002

typedef struct {
        unsigned int flags;

        unsigned int mem_lower;
        unsigned int mem_upper;

        unsigned int boot_device;

        unsigned char* cmdline;
        unsigned int mods_count;
        unsigned int* mods_addr;
} multiboot_boot_info;
#warning "structure multiboot_boot_info is not fully complete!"
