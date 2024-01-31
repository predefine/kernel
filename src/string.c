#include <string.h>
#include <stdio.h>

uint8_t memcmp(void* a, void* b, uint32_t size){
    while(size-- > 0)
        if(*(uint8_t*)a++ != *(uint8_t*)b++)
            return 1;
    return 0;
}
