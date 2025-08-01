#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

#define VIOS_MAX_PATH 108

// Kernel entry point
void kernel_main(void);

// Kernel panic handler - halts execution
void panic(const char *msg);

// Prints a null-terminated string to the terminal
void print(const char *str);

// Enables kernel paging and switches to the kernel page directory
void kernel_page(void);

// Registers kernel registers or setups CPU state (assumed)
void kernel_registers(void);

// Converts integer to ASCII string (null-terminated)
void int_to_ascii(int num, char *str);

// Writes a character with color to the terminal at current cursor
void terminal_writechar(char c, char colour);

// Converts foreground and background colors to VGA color byte
uint8_t convert_color(int fg, int bg);

// Error handling macros
#define ERROR(value) ((void *)(value))
#define ERROR_I(value) ((int)(value))
#define ISERR(value) ((int)(value) < 0)

#endif // KERNEL_H