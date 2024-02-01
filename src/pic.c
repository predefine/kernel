#include <pic.h>
#include <idt.h>
#include <asm.h>

#define PIC1_CMD     0x20
#define PIC1_DATA    0x21
#define PIC2_CMD     0xa0
#define PIC2_DATA    0xa1

#define PIC_CMD_EOI  0x20
#define PIC_READ_ISR 0x0b

#define ICW1_INIT    0x10
#define ICW1_ICW4    0x01
#define ICW4_8086    0x01

uint8_t pic_get_irq(uint8_t pic){
    uint8_t pic_io = !pic ? PIC1_CMD : PIC2_CMD;
    outb(pic_io, PIC_READ_ISR);
    uint8_t isr = inb(pic_io);
    uint8_t irq = 0;
    while(!(isr&1) && irq<8){
        irq++;
        isr>>=1;
    }
    if(irq == 8) return 0xff; // 0xff = no irq
    return irq;
}

void pic_outb(uint32_t port, uint8_t data){
    outb(port, data);
    io_wait();
}

extern void pic_irq_handler_asm(void);
__asm__ (
"pic_irq_handler_asm:"
"   pushal ;"
"   call pic_irq_handler ;"
"   call pic_send_eoi ;"
"   popal ;"
"   iret;"
);

static pic_irq_handler_function pic_irq_handlers_table [16];

void pic_irq_handler(void){
    uint8_t irq = pic_get_irq(1);
    if(irq != 0xff)
        irq |= 8;
    else
        irq = pic_get_irq(0);
    pic_irq_handler_function handler = pic_irq_handlers_table[irq];
    if(handler != 0)
        handler();
}

void pic_set_irq_handler(uint8_t irq, pic_irq_handler_function handler){
    if(irq<16)
        pic_irq_handlers_table[irq] = handler;
}

void pic_idt_setup(){
    for(uint8_t vector = 0x20; vector <= 0x28; vector++){
        idt_set_descriptor(vector, pic_irq_handler_asm, 0x8E);
    }
}

void pic_init(){

    pic_outb(PIC1_CMD, ICW1_INIT | ICW1_ICW4);
    pic_outb(PIC2_CMD, ICW1_INIT | ICW1_ICW4);

    pic_outb(PIC1_DATA, 0x20);
    pic_outb(PIC2_DATA, 0x28);

    pic_outb(PIC1_DATA, 4);
    pic_outb(PIC2_DATA, 2);

    pic_outb(PIC1_DATA, ICW4_8086);
    pic_outb(PIC2_DATA, ICW4_8086);

    pic_disable();
    pic_idt_setup();
    pic_enable();
}

void pic_send_eoi(){
    if(pic_get_irq(1) != 0xff)
        outb(PIC2_CMD, PIC_CMD_EOI);
    outb(PIC1_CMD, PIC_CMD_EOI);
}

void pic_disable(){
    pic_outb(PIC1_DATA, 0xff);
    pic_outb(PIC2_DATA, 0xff);
}

void pic_enable(){
    pic_outb(PIC1_DATA, 0x0);
    pic_outb(PIC2_DATA, 0x0);
}
