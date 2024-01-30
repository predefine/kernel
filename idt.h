#pragma once

typedef struct {
    unsigned short offset1;
    unsigned short segment;
    unsigned char res;
    unsigned char attr;
    unsigned short offset2;
} __attribute__((packed)) idt_entry;

typedef struct {
    unsigned short size;
    unsigned int* offset;
} __attribute__((packed)) idt_descriptor;

void idt_set_descriptor(unsigned char vector, void* isr, unsigned char flags);
void idt_init();
