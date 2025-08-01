#include "string.h"
#include <stddef.h>

static int int_to_str(int value, char* buffer, int bufsize) {
    int pos = 0;
    bool negative = false;

    if (value < 0) {
        negative = true;
        value = -value;
    }

    // Write digits in reverse order
    char temp[20];
    int i = 0;
    do {
        temp[i++] = (value % 10) + '0';
        value /= 10;
    } while (value > 0);

    if (negative) {
        temp[i++] = '-';
    }

    // Reverse into output buffer
    int len = i;
    if (bufsize > 0) {
        for (int j = 0; j < i && pos < bufsize; j++) {
            buffer[pos++] = temp[i - j - 1];
        }
    }

    return len; // length of string written (or would be)
}

char tolower(char s1)
{
    if (s1 >= 65 && s1 <= 90)
    {
        s1 += 32;
    }

    return s1;
}

int strlen(const char *ptr)
{
    int i = 0;
    while (*ptr != 0)
    {
        i++;
        ptr += 1;
    }

    return i;
}

int strnlen(const char *ptr, int max)
{
    int i = 0;
    for (i = 0; i < max; i++)
    {
        if (ptr[i] == 0)
            break;
    }

    return i;
}

int strnlen_terminator(const char *str, int max, char terminator)
{
    int i = 0;
    for (i = 0; i < max; i++)
    {
        if (str[i] == '\0' || str[i] == terminator)
            break;
    }

    return i;
}

int istrncmp(const char *s1, const char *s2, int n)
{
    unsigned char u1, u2;
    while (n-- > 0)
    {
        u1 = (unsigned char)*s1++;
        u2 = (unsigned char)*s2++;
        if (u1 != u2 && tolower(u1) != tolower(u2))
            return u1 - u2;
        if (u1 == '\0')
            return 0;
    }

    return 0;
}
int strncmp(const char *str1, const char *str2, int n)
{
    unsigned char u1, u2;

    while (n-- > 0)
    {
        u1 = (unsigned char)*str1++;
        u2 = (unsigned char)*str2++;
        if (u1 != u2)
            return u1 - u2;
        if (u1 == '\0')
            return 0;
    }

    return 0;
}

char *strcpy(char *dest, const char *src)
{
    char *res = dest;
    while (*src != 0)
    {
        *dest = *src;
        src += 1;
        dest += 1;
    }

    *dest = 0x00;

    return res;
}

char *strncpy(char *dest, const char *src, int count)
{
    int i = 0;
    for (i = 0; i < count - 1; i++)
    {
        if (src[i] == 0x00)
            break;

        dest[i] = src[i];
    }

    dest[i] = 0x00;
    return dest;
}

bool isdigit(char c)
{
    return c >= 48 && c <= 57;
}
int tonumericdigit(char c)
{
    return c - 48;
}

char *sp = 0;
char *strtok(char *str, const char *delimiters)
{
    int i = 0;
    int len = strlen(delimiters);
    if (!str && !sp)
        return 0;

    if (str && !sp)
    {
        sp = str;
    }

    char *p_start = sp;
    while (1)
    {
        for (i = 0; i < len; i++)
        {
            if (*p_start == delimiters[i])
            {
                p_start++;
                break;
            }
        }

        if (i == len)
        {
            sp = p_start;
            break;
        }
    }

    if (*sp == '\0')
    {
        sp = 0;
        return sp;
    }

    // Find end of substring
    while (*sp != '\0')
    {
        for (i = 0; i < len; i++)
        {
            if (*sp == delimiters[i])
            {
                *sp = '\0';
                break;
            }
        }

        sp++;
        if (i < len)
            break;
    }

    return p_start;
}

char *strchr(const char *str, int ch) {
    while (*str != '\0')
    {
        if (*str == (char)ch)
        {
            return (char *)str; // Cast to non-const because return type is non-const
        }
        str++;
    }

    // Check if ch is '\0' to match behavior of standard strchr
    if (ch == '\0')
    {
        return (char *)str;
    }

    return 0x00;
}

int snprintf(char *buffer, size_t size, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    size_t i = 0; // buffer index
    const char *p = format;

    while (*p && i < size - 1)
    {
        if (*p == '%')
        {
            ++p;
            if (*p == 's')
            {
                const char *str = va_arg(args, const char *);
                while (*str && i < size - 1)
                {
                    buffer[i++] = *str++;
                }
            }
            else if (*p == 'd')
            {
                int val = va_arg(args, int);
                char num[12];
                int n = 0;
                if (val < 0)
                {
                    if (i < size - 1)
                        buffer[i++] = '-';
                    val = -val;
                }
                do
                {
                    num[n++] = '0' + val % 10;
                    val /= 10;
                } while (val > 0 && n < sizeof(num));
                while (n-- > 0 && i < size - 1)
                {
                    buffer[i++] = num[n];
                }
            }
            else if (*p == 'c')
            {
                char c = (char)va_arg(args, int);
                if (i < size - 1)
                    buffer[i++] = c;
            }
            else
            {
                // Unsupported, treat as literal
                if (i < size - 1)
                    buffer[i++] = '%';
                if (i < size - 1)
                    buffer[i++] = *p;
            }
        }
        else
        {
            buffer[i++] = *p;
        }
        ++p;
    }

    buffer[i] = '\0';
    va_end(args);
    return (int)i;
}