#include "fs.h"
#include <tar.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define TAR_PADDING 0x200

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

void tar_open(file* _file, filesystem_info* filesystem){
    void* tar_address = (void*)filesystem->address;
    uint32_t tar_size = filesystem->size;
    uint32_t pos = 0;
    _file->type = FILETYPE_NONE;
    while((uint32_t)tar_address + pos != tar_size){
        tar_entry* entry = tar_address + pos;
        if(!*entry->filename) continue;

        _file->entry_offset = pos;
        pos += padded(sizeof(tar_entry));
        _file->data_offset = pos;
        _file->filesize = oct2bin(entry->size, 12);
        pos += padded(_file->filesize);

        if(memcmp(entry->filename, _file->filename, 100)) continue;
        if(entry->type == TAR_TYPE_FILE)
            _file->type = FILETYPE_FILE;
        else if(entry->type == TAR_TYPE_DIRECTORY)
            _file->type = FILETYPE_DIRECTORY;
        else
            break;
        _file->pos = 0;
        break;
    }
}
