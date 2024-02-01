#pragma once

#include <stdint.h>

#define KEYBOARD_IRQ_NUMBER 1

typedef struct {
    uint8_t scancode;
    uint8_t extended;
} keyboard_data;

void keyboard_init();
keyboard_data keyboard_read_byte();
