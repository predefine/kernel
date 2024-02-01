#include <keyboard.h>
#include <pic.h>
#include <i8042.h>
#include <asm.h>

#define KEYBOARD_EXTENDED_BYTE 0xe0

#define KEYBOARD_FLAGS_EXTENDED 1<<0
#define KEYBOARD_FLAGS_FULL     1<<7
static uint8_t keyboard_flags = 0;
static uint8_t keyboard_scancode = 0;

keyboard_data keyboard_read_byte(){
    keyboard_data data;
    while(!(keyboard_flags & KEYBOARD_FLAGS_FULL)) __asm__("pause");
    data.extended = !!(keyboard_flags & KEYBOARD_EXTENDED_BYTE);
    data.scancode = keyboard_scancode;
    keyboard_flags &= ~(KEYBOARD_FLAGS_FULL | KEYBOARD_FLAGS_EXTENDED);
    return data;
}

void keyboard_irq_handler(){
    // putc('!');
    while((keyboard_flags & KEYBOARD_FLAGS_FULL) && !(i8042_get_status() & I8042_STATUS_OUTPUT_BUFFER)) __asm__("pause");
    uint8_t data = i8042_read_byte();
    if(data == KEYBOARD_EXTENDED_BYTE && !(keyboard_flags & KEYBOARD_FLAGS_EXTENDED))
        keyboard_flags |= KEYBOARD_FLAGS_EXTENDED;
    else {
        keyboard_scancode = data;
        keyboard_flags |= KEYBOARD_FLAGS_FULL;
    }
}

void keyboard_init(){
    pic_set_irq_handler(KEYBOARD_IRQ_NUMBER, keyboard_irq_handler);
}
