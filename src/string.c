#include <string.h>

uint8_t memcmp(uint8_t* a, uint8_t* b, uint32_t size){
    while(size-- > 0)
        if(*a++ != *b++)
            return 1;
    return 0;
}

void memcpy(uint8_t* dest, const uint8_t* src, uint32_t size){
    while(size-- > 0)
        *dest++ = *src++;
}

uint32_t strlen(char* str){
    uint32_t len = 0;
    while(*str++) len++;
    return len;
}

void char_ptr_to_array(char* name, char name2[], uint32_t size){
    uint32_t pos = 0;
    while(*name != 0  && pos < size){
        name2[pos++] = *name++;
    }
    name2[pos++] = 0;
}

