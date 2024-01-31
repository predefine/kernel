#pragma once

#include <stdint.h>

typedef struct {
    uint16_t offset1;
    uint16_t segment;
    uint8_t res;
    uint8_t attr;
    uint16_t offset2;
} __attribute__((packed)) idt_entry;

typedef struct {
    uint16_t size;
    uint32_t* offset;
} __attribute__((packed)) idt_descriptor;

typedef void (*idt_handler_function)();

void idt_set_descriptor(uint8_t vector, idt_handler_function isr, uint8_t flags);
void idt_init();
