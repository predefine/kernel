#include <string.h>
#include <stdio.h>

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
