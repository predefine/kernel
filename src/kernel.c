#include <fs.h>
#include <stdint.h>
#include <stdio.h>
#include <idt.h>
#include <pic.h>
#include <multiboot.h>
#include <keyboard.h>
#include <tar.h>

void timer_irq(){
    putc('.');
}

void kmain(unsigned long magic, multiboot_boot_info* info){
    if(magic!=MULTIBOOT_BOOTLOADER_MAGIC){
        puts("Booting without mutliboot 1 is not possible :(");
        return;
    }
    idt_init();
    pic_init();
    keyboard_init();

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
        filesystem_info fs;
        fs.address = module->mod_start;
        fs.size = module->mod_end - module->mod_start;
        uint32_t fd = fs_open("dir2/file2.txt", &fs, &tar_fs_ops);
        puts("File fd: ");
        putint(fd);
        putc('\n');
        puts("File size: ");
        putint(fs_getsize(fd, &fs, &tar_fs_ops));
        putc('\n');
        #define READ_TEST_BUFFER 1000
        char buffer[READ_TEST_BUFFER];
        uint32_t readed = fs_read(fd, (char*)&buffer[0], READ_TEST_BUFFER, &fs, &tar_fs_ops);
        puts("Readed: ");
        putint(readed);
        putc('\n');
        puts(buffer);
        putc('\n');
        fs_close(fd, &fs, &tar_fs_ops);
        puts("File size after close: ");
        putint(fs_getsize(fd, &fs, &tar_fs_ops));
        putc('\n');

        char files[READDIR_FILES_MAX][FILENAME_MAX];
        uint32_t readdir_total = fs_readdir("/dir1", 5, files, &fs, &tar_fs_ops);
        puts("Files in directory: ");
        putint(readdir_total);
        putc('\n');
        for(uint32_t i = 0; i < readdir_total; i++){
            puts(files[i]);
            putc('\n');
        }
    }

    while(1){
        keyboard_data data = keyboard_read_byte();
        puts("Readed ");
        if(data.extended) puts("extended ");
        puts("scancode: ");
        puthex(data.scancode);
        putc('\n');
    }

    // pic_set_irq_handler(0, timer_irq);

    for(;;);
}
