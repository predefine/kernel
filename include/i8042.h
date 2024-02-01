#pragma once

#include <stdint.h>

#define I8042_DATA_PORT 0x60
#define I8042_STATUS_REGISTER 0x64
#define I8042_COMMAND_REGISTER 0x64

#define I8042_STATUS_OUTPUT_BUFFER 1<<0
#define I8042_STATUS_INPUT_BUFFER 1<<1

uint8_t i8042_get_status();
uint8_t i8042_read_byte();
