#include <pic.h>
#include <idt.h>
#include <asm.h>
#include <io.h>

#define PIC1_CMD     0x20
#define PIC1_DATA    0x21
#define PIC2_CMD     0xa0
#define PIC2_DATA    0xa1

#define PIC_CMD_EOI  0x20
#define PIC_READ_ISR 0x0b

#define ICW1_INIT    0x10
#define ICW1_ICW4    0x01
#define ICW4_8086    0x01

unsigned char pic_get_irq(unsigned char pic){
    unsigned char pic_io = !pic ? PIC1_CMD : PIC2_CMD;
    outb(pic_io, PIC_READ_ISR);
    unsigned char isr = inb(pic_io);
    unsigned char irq = 0;
    while(!(isr&1) && irq<8){
        irq++;
        isr>>=1;
    }
    if(irq == 8) return 0xff; // 0xff = no irq
    return irq;
}

void pic_outb(unsigned int port, unsigned char data){
    outb(port, data);
    io_wait();
}


struct interrupt_frame {
    unsigned int ip;
    unsigned int cs;
    unsigned int flags;
    unsigned int sp;
    unsigned int ss;
} __attribute__((packed));

extern void pic_irq_handler_asm(void);

static void* pic_irq_handlers_table [16];

void pic_irq_handler(void){
    unsigned int irq = pic_get_irq(1);
    if(irq != 0xff)
        irq |= 8;
    else
        irq = pic_get_irq(0);
    void* handler = pic_irq_handlers_table[irq];
    if(handler != 0)
        (*(void(*)(void))(pic_irq_handlers_table[irq]))();
}

void pic_set_irq_handler(unsigned char irq, void* handler){
    if(irq<16)
        pic_irq_handlers_table[irq] = handler;
}

__asm__ (
"esp_back: .long 0 ;"
"pic_irq_handler_asm:"
"   pushal ;"
"   movl %esp, esp_back ;"
"   call pic_irq_handler ;"
"   call pic_send_eoi ;"
"   movl esp_back, %esp ;"
"   popal ;"
"   iret"
);

void pic_idt_setup(){
    for(unsigned char vector = 0x20; vector <= 0x28; vector++){
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
