#pragma once

#include <stdint.h>
#include <fs.h>

typedef enum {
    TAR_TYPE_FILE = '0',
    TAR_TYPE_DIRECTORY = '5'
} tar_type;

typedef struct {
    uint8_t filename[100];
    uint8_t mode[8];
    uint8_t ouid[8];
    uint8_t ogid[8];
    uint8_t size[12];
    uint8_t last_mod[12];
    uint8_t checksum[8];
    tar_type type;
    uint8_t linked_name[100];
    uint8_t ustar[6];
    uint8_t ustar_version[2];
    uint8_t owner_username[32];
    uint8_t owner_groupname[32];
    uint8_t device_major[8];
    uint8_t device_minor[8];
    uint8_t file_path[155];
} __attribute__((packed)) tar_entry;

void tar_open(file* _file, filesystem_info* filesystem);

// void tar_load(void* addr, uint32_t end);
