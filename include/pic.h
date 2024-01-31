#pragma once

#include <stdint.h>

typedef void (*pic_irq_handler_function)();

void pic_set_irq_handler(uint8_t irq, pic_irq_handler_function handler);
void pic_disable();
void pic_enable();
void pic_init();
