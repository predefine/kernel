#pragma once

#include <stdint.h>

uint8_t memcmp(uint8_t* a, uint8_t* b, uint32_t size);
void memcpy(uint8_t* dest, const uint8_t* src, uint32_t size);
uint32_t strlen(char* str);
void char_ptr_to_array(char* name, char name2[], uint32_t size);
