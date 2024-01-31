#include <fs.h>
#include <stdint.h>
#include <stdio.h>
#include <idt.h>
#include <pic.h>
#include <asm.h>
#include <multiboot.h>
#include <tar.h>

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


    if(info->flags & MULTIBOOT_INFO_MODS && info->mods_count > 0){
        multiboot_module_t* module = (multiboot_module_t*)info->mods_addr;
        file myfile;
        myfile.filename[0]='m';
        myfile.filename[1]='y';
        myfile.filename[2]='f';
        myfile.filename[3]='i';
        myfile.filename[4]='l';
        myfile.filename[5]='e';
        myfile.filename[6]='.';
        myfile.filename[7]='t';
        myfile.filename[8]='x';
        myfile.filename[9]='t';
        myfile.filename[10]=0;
        filesystem_info fs;
        fs.address = module->mod_start;
        fs.size = module->mod_end - module->mod_start;
        tar_open(&myfile, &fs);
        putint(myfile.filesize);
    }

    pic_set_irq_handler(0, timer_irq);
    pic_set_irq_handler(1, ps2_irq);

    for(;;);
}
