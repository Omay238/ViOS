#include "vios.h"
#include "string.h"

struct command_argument *vios_parse_command(const char *command, int max)
{
    struct command_argument *root_command = 0;
    char scommand[1025];
    if (max >= (int)sizeof(scommand))
    {
        return 0;
    }

    strncpy(scommand, command, sizeof(scommand));
    scommand[sizeof(scommand) - 1] = 0; // Ensure null-termination
    char *token = strtok(scommand, " ");
    if (!token)
    {
        goto out;
    }

    root_command = vios_malloc(sizeof(struct command_argument));
    if (!root_command)
    {
        goto out;
    }

    strncpy(root_command->argument, token, sizeof(root_command->argument));
    root_command->argument[sizeof(root_command->argument) - 1] = 0; // Ensure null-termination
    root_command->next = 0;

    struct command_argument *current = root_command;
    token = strtok(NULL, " ");
    while (token != 0)
    {
        struct command_argument *new_command = vios_malloc(sizeof(struct command_argument));
        if (!new_command)
        {
            break;
        }

        strncpy(new_command->argument, token, sizeof(new_command->argument));
        new_command->argument[sizeof(new_command->argument) - 1] = 0; // Ensure null-termination
        new_command->next = 0x00;
        current->next = new_command;
        current = new_command;
        token = strtok(NULL, " ");
    }
out:
    return root_command;
}

int vios_getkeyblock()
{
    int val = 0;
    do
    {
        val = vios_getkey();
    } while (val == 0);
    return val;
}

void vios_terminal_readline(char *out, int max, bool output_while_typing)
{
    int i = 0;

    while (i < max - 1)
    {
        char key = vios_getkeyblock();

        if (key == 13) // Enter
        {
            break;
        }

        if (key == 0x08) // Backspace
        {
            if (i > 0)
            {
                i--;
                out[i] = '\0';

                if (output_while_typing)
                {
                    vios_putchar('\b');
                    vios_putchar(' ');
                    vios_putchar('\b');
                }
            }
            continue; // Skip rest of loop
        }

        // Optional: filter to printable characters
        if (key >= 32 && key <= 126)
        {
            out[i++] = key;

            if (output_while_typing)
            {
                vios_putchar(key);
            }
        }
    }

    out[i] = '\0';
}

int vios_system_run(const char *command)
{
    char buf[1024];
    strncpy(buf, command, sizeof(buf));
    buf[sizeof(buf) - 1] = 0;
    struct command_argument *root_command_argument = vios_parse_command(buf, sizeof(buf));
    buf[sizeof(buf) - 1] = 0;
    if (!root_command_argument)
    {
        return -1;
    }

    int result = vios_system(root_command_argument);
    // Clean up allocated command arguments
    struct command_argument *current = root_command_argument;
    while (current)
    {
        struct command_argument *next = current->next;
        vios_free(current);
        current = next;
    }

    return result;
}