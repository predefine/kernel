#include <stdio.h>

static char color = 0xf;
static int pos = 0;
static char width = 80;
static char height = 25;
static int size;
static uint16_t* vga_buffer = (uint16_t*)0xb8000;

void clear_display(){
    size = width*height;
    for(int i = 0; i < width * height; i++){
        vga_buffer[i] = 0;
    }
    pos = 0;
}

void scroll(){
    for(int y = 0; y < height-1; y++)
        for(int i = 0; i < width; i++){
            int pos = y*width+i;
            vga_buffer[pos] = vga_buffer[pos+width];
        }
    pos = width*(height-1);
    for(int i = 0; i < width; i++) vga_buffer[pos + i] = 0;
}

void putc(char c){
    if(pos == size){
        scroll();
    }
    if (c == '\n'){
        pos += width - (pos%width);
        return ;
    }
    if (c == '\b'){
        vga_buffer[--pos] = 0;
        return;
    }
    if (c == '\r'){
        pos -= pos%width;
        return;
    }
    vga_buffer[pos++] = (color<<8) | c;
}

void putint(uint32_t val){
    if(val == 0) putc('0');
    uint8_t out[10];
    uint8_t pos = 0;
    while(val > 0){
        out[pos++] = '0'+(val % 10);
        val /= 10;
    }
    while(pos){
        putc(out[--pos]);
    }
}


static const char hexchars[16] = "0123456789abcdef";

void puthex(uint32_t val){
    if(val == 0) putc('0');
    uint8_t out[4];
    uint8_t pos = 0;
    while(val > 0){
        out[pos++] = hexchars[val%0xf];
        val >>= 4;
    }
    while(pos){
        putc(out[--pos]);
    }
}

void puts(const char* str){
    while(*str){
        putc(*str);
        str++;
    }
}
