#pragma once

#include <stdint.h>

#define FILENAME_MAX 128
#define PATH_MAX 128

#define FD_MAX 32

typedef enum {
    FILETYPE_NONE = 0,
    FILETYPE_FILE = 1,
    FILETYPE_DIRECTORY = 2
} fs_filetype;

typedef struct {
    uint8_t filename[FILENAME_MAX];
    uint8_t path[PATH_MAX];
    uint32_t filesize;
    fs_filetype type;
    uint32_t data_offset;
    uint32_t entry_offset;
    uint32_t pos;
} __attribute__((packed)) file;

typedef struct {
    uint32_t address;
    uint32_t size;
} __attribute__((packed)) filesystem_info;

uint32_t fs_open(char* name, filesystem_info* filesystem);
uint32_t fs_getsize(uint32_t fd);
