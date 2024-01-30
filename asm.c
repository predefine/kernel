#include <asm.h>

void outb(unsigned int port, unsigned char val)
{
    asm volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

unsigned char inb(unsigned int port)
{
    unsigned char ret;
    asm volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

void io_wait(void)
{
    outb(0x80, 0);
}
