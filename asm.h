#pragma once

void outb(unsigned int port, unsigned char val);
unsigned char inb(unsigned int port);
void io_wait(void);
