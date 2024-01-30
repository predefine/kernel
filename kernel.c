#include <io.h>
#include <idt.h>
#include <pic.h>
#include <asm.h>

void timer_irq(){
    putc('.');
}
void ps2_irq(){
    (void)inb(0x60);
    putc('?');
}

void kmain(){
    idt_init();
    pic_init();

    clear_display();
    puts("Hello, os!\nSimplest stdio :D\n");

    //print "multiline works too :D\n"
    puts("multiline works too :P\bD\n");

    pic_set_irq_handler(0, timer_irq);
    pic_set_irq_handler(1, ps2_irq);

    for(;;);
}
