#pragma once

#include <stdint.h>

#define MULTIBOOT_INFO_MEMORY 1
#define MULTIBOOT_INFO_BOOTDEV 1<<1
#define MULTIBOOT_INFO_CMDLINE 1<<2
#define MULTIBOOT_INFO_MODS 1<<3

#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002

typedef struct {
        uint32_t flags;

        uint32_t mem_lower;
        uint32_t mem_upper;

        uint32_t boot_device;

        uint8_t* cmdline;
        uint32_t mods_count;
        uint32_t* mods_addr;
} multiboot_boot_info;

typedef struct {
        uint32_t mod_start;
        uint32_t mod_end;

        uint32_t cmdline;

        uint32_t _pad;
} multiboot_module_t;
#warning "structure multiboot_boot_info is not fully complete!"
