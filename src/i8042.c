#include <i8042.h>
#include <asm.h>

uint8_t i8042_get_status(){
    return inb(I8042_STATUS_REGISTER);
}

uint8_t i8042_read_byte(){
    while(!(i8042_get_status() & I8042_STATUS_OUTPUT_BUFFER)) __asm__("pause");
    return inb(I8042_DATA_PORT);
}
