#pragma once

void pic_set_irq_handler(unsigned char irq, void* handler);
void pic_disable();
void pic_enable();
void pic_init();
