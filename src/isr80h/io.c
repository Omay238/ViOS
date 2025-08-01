#include "io.h"
#include "task/task.h"
#include "terminal/terminal.h"
#include "keyboard/keyboard.h"
#include "rtc/rtc.h"

void *isr80h_command1_print(struct interrupt_frame *frame)
{
    void *user_space_msg_buffer = task_get_stack_item(task_current(), 0);
    char buf[1024];
    copy_string_from_task(task_current(), user_space_msg_buffer, buf, sizeof(buf));

    print(buf);
    return 0;
}

void *isr80h_command2_getkey(struct interrupt_frame *frame)
{
    char c = keyboard_pop();
    return (void *)((int)c);
}

void *isr80h_command3_putchar(struct interrupt_frame *frame)
{
    char c = (char)(int)task_get_stack_item(task_current(), 0);
    terminal_writechar(c, convert_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
    return 0;
}

void *isr80h_command9_sleep(struct interrupt_frame *frame)
{
    int seconds = (int)task_get_stack_item(task_current(), 0);
    if (seconds < 0)
    {
        return (void *)-1; // Return error for negative values
    }
    sleep_seconds(seconds);
    return 0;
}