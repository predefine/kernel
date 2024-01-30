#include <io.h>
#include <idt.h>
#include <pic.h>
#include <asm.h>
#include <multiboot.h>

void timer_irq(){
    putc('.');
}
void ps2_irq(){
    (void)inb(0x60);
    putc('?');
}

void kmain(unsigned long magic, multiboot_boot_info* info){
    if(magic!=MULTIBOOT_BOOTLOADER_MAGIC){
        puts("Booting without mutliboot 1 is not possible :(");
        return;
    }
    idt_init();
    pic_init();



    clear_display();
    puts("Hello, os!\nSimplest stdio :D\n");

    //print "multiline works too :D\n"
    puts("multiline works too :P\bD\n");

    if(info->flags & MULTIBOOT_INFO_CMDLINE){
        puts("Kernel cmdline is: ");
        puts((const char*)info->cmdline);
    } else {
        puts("No cmdline!");
    }

    putc('\n');

    pic_set_irq_handler(0, timer_irq);
    pic_set_irq_handler(1, ps2_irq);

    for(;;);
}
