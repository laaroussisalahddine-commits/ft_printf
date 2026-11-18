#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include "ft_printf.h"

typedef struct s_case
{
    const char *name;
    const char *fmt;
    unsigned int value;
} t_case;

/* Capture exactly what each function writes to stdout, including NUL bytes. */
static int capture(const char *fmt, unsigned int value, int custom,
                   char *output, size_t capacity, size_t *length)
{
    int saved_fd;
    FILE *tmp;
    long size;
    int result;

    fflush(stdout);
    saved_fd = dup(STDOUT_FILENO);
    tmp = tmpfile();
    if (saved_fd < 0 || !tmp || dup2(fileno(tmp), STDOUT_FILENO) < 0)
    {
        if (saved_fd >= 0)
            close(saved_fd);
        if (tmp)
            fclose(tmp);
        return (-9999);
    }
    if (custom)
        result = ft_printf(fmt, value);
    else
        result = printf(fmt, value);
    fflush(stdout);
    size = ftell(tmp);
    if (size < 0 || (size_t)size >= capacity || fseek(tmp, 0, SEEK_SET))
        size = -1;
    if (size >= 0 && fread(output, 1, (size_t)size, tmp) != (size_t)size)
        size = -1;
    dup2(saved_fd, STDOUT_FILENO);
    close(saved_fd);
    fclose(tmp);
    if (size < 0)
        return (-9999);
    *length = (size_t)size;
    output[size] = '\0';
    return (result);
}

static void show_bytes(const char *buf, size_t n)
{
    size_t i;

    putchar('"');
    i = 0;
    while (i < n)
    {
        if (buf[i] == '\n')
            printf("\\n");
        else if (buf[i] == '\t')
            printf("\\t");
        else if (buf[i] == ' ')
            printf("[space]");
        else if ((unsigned char)buf[i] < 32 || (unsigned char)buf[i] > 126)
            printf("\\x%02X", (unsigned char)buf[i]);
        else
            putchar(buf[i]);
        i++;
    }
    puts("\"");
}

int main(void)
{
    static const t_case cases[] = {
        {"x zero",             "%#x",         0u},
        {"x one",              "%#x",         1u},
        {"x nine",             "%#x",         9u},
        {"x ten",              "%#x",        10u},
        {"x fifteen",          "%#x",        15u},
        {"x sixteen",          "%#x",        16u},
        {"x thirty one",       "%#x",        31u},
        {"x 42",               "%#x",        42u},
        {"x 255",              "%#x",       255u},
        {"x 256",              "%#x",       256u},
        {"x 0xabcdef",         "%#x",  0xabcdefu},
        {"x INT_MAX",          "%#x",   INT_MAX},
        {"x UINT_MAX",         "%#x",  UINT_MAX},
        {"x high bit",         "%#x", 0x80000000u},
        {"x literal wrapper",  "A[%#x]Z",    42u},
        {"X zero",             "%#X",         0u},
        {"X one",              "%#X",         1u},
        {"X nine",             "%#X",         9u},
        {"X ten",              "%#X",        10u},
        {"X fifteen",          "%#X",        15u},
        {"X sixteen",          "%#X",        16u},
        {"X thirty one",       "%#X",        31u},
        {"X 42",               "%#X",        42u},
        {"X 255",              "%#X",       255u},
        {"X 256",              "%#X",       256u},
        {"X 0xabcdef",         "%#X",  0xabcdefu},
        {"X INT_MAX",          "%#X",   INT_MAX},
        {"X UINT_MAX",         "%#X",  UINT_MAX},
        {"X high bit",         "%#X", 0x80000000u},
        {"X literal wrapper",  "A[%#X]Z",    42u}
    };
    char expected[512];
    char yours[512];
    size_t e_len;
    size_t y_len;
    int e_ret;
    int y_ret;
    int passed;
    int ok;
    size_t i;

    passed = 0;
    for (i = 0; i < sizeof(cases) / sizeof(cases[0]); i++)
    {
        e_len = 0;
        y_len = 0;
        e_ret = capture(cases[i].fmt, cases[i].value, 0,
                        expected, sizeof(expected), &e_len);
        y_ret = capture(cases[i].fmt, cases[i].value, 1,
                        yours, sizeof(yours), &y_len);
        if (e_ret == -9999 || y_ret == -9999)
        {
            fprintf(stderr, "Capture failed on test %zu\n", i + 1);
            return (1);
        }
        ok = (e_ret == y_ret && e_len == y_len &&
              memcmp(expected, yours, e_len) == 0);
        passed += ok;
        printf("[%02zu] %-22s : %s\n", i + 1, cases[i].name,
               ok ? "PASS" : "FAIL");
        printf("     format=\"%s\" value=%u (0x%x)\n",
               cases[i].fmt, cases[i].value, cases[i].value);
        printf("     EXPECTED (libc): ret=%d bytes=", e_ret);
        show_bytes(expected, e_len);
        printf("     YOURS          : ret=%d bytes=", y_ret);
        show_bytes(yours, y_len);
    }
    printf("\nTOTAL: %d/30 PASS, %d FAIL\n", passed, 30 - passed);
    return (passed == 30 ? 0 : 1);
}
