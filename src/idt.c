#include <idt.h>
#include <stdio.h>

idt_entry idt_table[256];

void idt_set_descriptor(uint8_t vector, idt_handler_function isr, uint8_t flags){
    idt_entry* entry = &idt_table[vector];

    entry->offset1 = (uint32_t)isr & 0xffff;
    entry->offset2 = (uint32_t)isr >> 16;
    entry->segment = 0x08;
    entry->attr = flags;
    entry->res = 0;
}

// __attribute__((noreturn))
void exception_handler(){
    puts("pernel kanic!");
    __asm__ volatile ("cli; hlt");
}

void idt_init(){
    idt_descriptor idtr;
    idtr.size = sizeof(idt_entry) * 256 - 1;
    idtr.offset = (uint32_t*)&idt_table[0];

    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, exception_handler, 0x8E);
    }

    __asm__ volatile ("lidt %0; sti" :: "m"(idtr));

    return;
}
