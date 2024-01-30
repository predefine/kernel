#pragma once

#include <stdint.h>

void clear_display();
void putc(char c);
void puts(const char* str);
void putint(uint32_t val);
void puthex(uint32_t val);
