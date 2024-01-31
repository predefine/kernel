#include <tar.h>
#include <stdio.h>
#include <stdint.h>

#define TAR_PADDING 0x200

typedef struct {
    uint8_t filename[100];
    uint8_t mode[8];
    uint8_t ouid[8];
    uint8_t ogid[8];
    uint8_t size[12];
    uint8_t last_mod[12];
    uint8_t checksum[8];
    uint8_t type;
    uint8_t linked_name[100];
    uint8_t ustar[6];
    uint8_t ustar_version[2];
    uint8_t owner_username[32];
    uint8_t owner_groupname[32];
    uint8_t device_major[8];
    uint8_t device_minor[8];
    uint8_t filename_prefix[155];
} /*__attribute__((packed))*/ tar_entry;

uint32_t oct2bin(uint8_t* str, int size){
    uint32_t count = 0;
    for (int i = 0; i < size; i++)
        count = count << 3 | (str[i - 1] - '0');
    return count;
}

uint32_t padded(uint32_t value){
    if(value % TAR_PADDING > 0)
        value += TAR_PADDING - (value%TAR_PADDING);
    return value;
}

void tar_load(void* addr, uint32_t end){
    uint32_t pos = 0;
    while((uint32_t)addr+pos != end){
        tar_entry* entry = addr+pos;

        // We cant have file without name, maybe we at end of tar!
        if(!*entry->filename)break;

        uint32_t size = oct2bin(entry->size, 12);
        puts("Filename: ");
        puts((const char*)entry->filename);
        puts("\nSize: ");
        putint(size);
        putc('\n');
        pos += padded(sizeof(tar_entry));
        // Parse data here....
        pos += padded(size);

    }
}
