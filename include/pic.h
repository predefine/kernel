#pragma once

#include <stdint.h>

void pic_set_irq_handler(uint8_t irq, void* handler);
void pic_disable();
void pic_enable();
void pic_init();
