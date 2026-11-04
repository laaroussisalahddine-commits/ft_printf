#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "ft_printf.h"

/* Compile: cc -Wall -Wextra -Werror -I. printf_300_tests.c libftprintf.a libft.a -o printf_tests */
/* Uses fork() to isolate crashes and capture bytes + return value of each call. */

typedef struct s_result { unsigned char out[8192]; size_t len; int ret; int status; } t_result;
typedef struct s_case { const char *name; int kind; int index; } t_case;

/* Integer and string parameters are fixed so every generated invocation has matching types. */
static const int ints[] = {0, 1, -1, 42, -42, INT_MAX, INT_MIN, 7, -7, 100, -100, 214748, -214748, 255, -255, 16, -16, 123456789, -123456789, 9};
static const unsigned int uints[] = {0U, 1U, 42U, UINT_MAX, 7U, 100U, 255U, 16U, 65535U, 0xABCDEFU, 0x80000000U, 10U, 11U, 99U, 123456789U, 4000000000U, 4096U, 0xDEADBEEFU, 0x10000U, 999999U};
static const char *strings[] = {"", "a", "hello", "42", "hello world", "%%%%", "line\nnext", "tabs\there", " leading", "trailing ", "  both  ", "0123456789", "abcdef", "A", "12345678901234567890", "!@#$", "0", "longer string with spaces", "\n", "mixed\t\nend"};
static const int chars[] = {0, 'a', 'Z', '0', '%', ' ', '\n', '\t', 127, 1, 'X', '9', '!', '/', '+', '#', 255, 'b', 'Q', 42};
static int pointer_values[20];

/* Mandatory only: c s p d i u x X and percent. 15 families x 20 = 300. */
#define TESTS_PER_FAMILY 20
#define FAMILY_COUNT 15
#define TOTAL (TESTS_PER_FAMILY * FAMILY_COUNT)

#define DISPATCH(PF, I, F) do { \
  switch (F) { \
  case 0: return PF("%d", ints[I]); \
  case 1: return PF("%i", ints[I]); \
  case 2: return PF("%u", uints[I]); \
  case 3: return PF("%x", uints[I]); \
  case 4: return PF("%X", uints[I]); \
  case 5: return PF("%c", chars[I]); \
  case 6: return PF("%s", strings[I]); \
  case 7: return PF("%p", (void *)&pointer_values[I]); \
  case 8: return PF("prefix:%d:suffix", ints[I]); \
  case 9: return PF("%%|%x|%%", uints[I]); \
  case 10: return PF("%s|%d", strings[I], ints[I]); \
  case 11: return PF("%x|%X|%u", uints[I], uints[I], uints[I]); \
  case 12: return PF("[%c] %s [%c]", chars[I], strings[I], chars[I]); \
  case 13: return PF("ptr=%p unsigned=%u", (I % 4 == 0) ? (void *)0 : (void *)&pointer_values[I], uints[I]); \
  case 14: return PF("%d %i %u %x %X %c %s %% %p", ints[I], ints[I], uints[I], uints[I], uints[I], chars[I], strings[I], (void *)&pointer_values[I]); \
  default: return -999; \
  } \
} while (0)

/* Use an indirect function call so compiler cannot interpret nonliteral format strings. */
static int call_standard(int family, int i) { DISPATCH(printf, i, family); }
static int call_custom(int family, int i) { DISPATCH(ft_printf, i, family); }

static void run_one(int family, int i, int custom, t_result *r)
{
    int fd[2], rp[2], ws;
    pid_t pid;
    ssize_t n;
    unsigned char buf[1024];
    memset(r, 0, sizeof(*r));
    r->ret = -9999;
    if (pipe(fd) < 0 || pipe(rp) < 0) { perror("pipe"); exit(2); }
    fflush(NULL);
    pid = fork();
    if (pid < 0) { perror("fork"); exit(2); }
    if (pid == 0) {
        int ret;
        close(fd[0]); close(rp[0]);
        if (dup2(fd[1], STDOUT_FILENO) < 0) _exit(120);
        close(fd[1]);
        ret = custom ? call_custom(family, i) : call_standard(family, i);
        fflush(stdout);
        if (write(rp[1], &ret, sizeof(ret)) != sizeof(ret)) _exit(121);
        close(rp[1]);
        _exit(0);
    }
    close(fd[1]); close(rp[1]);
    while ((n = read(fd[0], buf, sizeof(buf))) > 0) {
        size_t use = (size_t)n;
        if (use > sizeof(r->out) - r->len) use = sizeof(r->out) - r->len;
        memcpy(r->out + r->len, buf, use); r->len += use;
    }
    close(fd[0]);
    if (read(rp[0], &r->ret, sizeof(r->ret)) != sizeof(r->ret)) r->ret = -9999;
    close(rp[0]);
    if (waitpid(pid, &ws, 0) < 0) { perror("waitpid"); exit(2); }
    r->status = WIFSIGNALED(ws) ? -WTERMSIG(ws) : (WIFEXITED(ws) ? WEXITSTATUS(ws) : -999);
}

static void show_bytes(const unsigned char *s, size_t n)
{
    size_t i;
    putchar('"');
    for (i = 0; i < n && i < 100; ++i) {
        if (s[i] == '\n') printf("\\n");
        else if (s[i] == '\t') printf("\\t");
        else if (s[i] == '\0') printf("\\0");
        else if (s[i] == '\r') printf("\\r");
        else if (s[i] < 32 || s[i] > 126) printf("\\x%02x", s[i]);
        else putchar(s[i]);
    }
    if (n > 100) printf("...");
    putchar('"');
}

int main(void)
{
    static const char *names[FAMILY_COUNT] = {
        "d", "i", "u", "x", "X", "c", "s", "p", "embedded-d", "percent-x",
        "mixed-s-d", "mixed-x-X-u", "mixed-c-s", "pointer-null-u", "all-mandatory"
    };
    t_result expected, actual;
    int family, i, failed = 0, passed = 0;
    for (i = 0; i < 20; ++i) pointer_values[i] = i * 37;
    for (family = 0; family < FAMILY_COUNT; ++family) {
        int family_fail = 0;
        printf("[%02d] %-16s ", family + 1, names[family]);
        fflush(stdout);
        for (i = 0; i < TESTS_PER_FAMILY; ++i) {
            run_one(family, i, 0, &expected);
            run_one(family, i, 1, &actual);
            if (actual.status != expected.status || actual.ret != expected.ret ||
                actual.len != expected.len || memcmp(actual.out, expected.out, expected.len)) {
                ++failed; ++family_fail;
                printf("\n  FAIL #%03d (family=%s, input=%d)\n", family * 20 + i + 1, names[family], i);
                printf("    libc: ret=%d status=%d len=%zu out=", expected.ret, expected.status, expected.len);
                show_bytes(expected.out, expected.len);
                printf("\n    ft  : ret=%d status=%d len=%zu out=", actual.ret, actual.status, actual.len);
                show_bytes(actual.out, actual.len);
                putchar('\n');
            } else ++passed;
        }
        printf(" %s (%d/20 passed)\n", family_fail ? "FAIL" : "OK", 20 - family_fail);
    }
    printf("\nTOTAL: %d/%d passed, %d failed\n", passed, TOTAL, failed);
    return failed ? 1 : 0;
}
