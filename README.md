*This project has been created as part of the 42 curriculum by slaarous*

# ft_printf

## Description

**ft_printf** is a C project from the 42 curriculum. Its goal is to recreate the essential behavior of the standard `printf()` function, using variadic arguments and writing formatted output to standard output.

The project builds a static library, `libftprintf.a`, which provides:

```c
int ft_printf(const char *format, ...);
```

The function returns the number of characters written, or `-1` if an output error is detected. The implementation focuses on the required conversions without implementing the full set of optional formatting flags, field widths, or precision supported by the standard `printf()`.

### Supported conversions

| Specifier | Meaning |
| --- | --- |
| `%c` | Print a character |
| `%s` | Print a string |
| `%p` | Print a pointer address in hexadecimal |
| `%d` | Print a signed decimal integer |
| `%i` | Print a signed decimal integer |
| `%u` | Print an unsigned decimal integer |
| `%x` | Print an unsigned integer in lowercase hexadecimal |
| `%X` | Print an unsigned integer in uppercase hexadecimal |
| `%%` | Print a literal percent sign |

## Algorithm and Data Structures

### 1. Reading variadic arguments

Unlike a regular function, `ft_printf` accepts a variable number of arguments. It uses the `<stdarg.h>` interface:

- `va_start` initializes access to the unnamed arguments.
- `va_arg` retrieves the next argument with the appropriate type.
- `va_end` finishes processing the argument list.

The format string determines which type to retrieve. For example, `%d` reads an `int`, `%u` reads an `unsigned int`, and `%p` reads a `void *`.

### 2. Parsing the format string

The algorithm scans the format string from left to right. Ordinary characters are written directly. When a `%` is encountered, the next character is interpreted as a conversion specifier and handled by the corresponding output routine. After that conversion, scanning continues until the end of the string.

This single-pass approach is appropriate because the required format is processed sequentially, without needing a syntax tree or an additional copy of the format string.

### 3. Converting numerical values

Decimal conversions use base 10, and hexadecimal conversions use base 16. The general method extracts digits using division and remainder:

- Remainder by the base gives the next digit.
- Division by the base removes that digit.
- Digits must be emitted in reverse order of extraction, for example by recursive output or a small temporary buffer.

Signed decimal values require extra care for negative numbers, especially `INT_MIN`, whose positive magnitude cannot be represented in a signed `int`. An adequately wide signed type can safely hold that magnitude before conversion.

For hexadecimal output, a digit lookup string (`0123456789abcdef` or `0123456789ABCDEF`) maps remainders to characters. A pointer is treated as an address value and represented in hexadecimal, subject to the platform's expected `%p` behavior.

### 4. Tracking the return value

Each output routine contributes the number of characters it writes. `ft_printf` accumulates these counts so its return value matches the length of the generated output, including spaces, signs, prefixes, and literal percent signs. Errors from `write` should be propagated rather than counted as successful output.

### 5. Data structure choice and justification

The program does not require a complex data structure. Its main state consists of:

- A `va_list` to access the variable arguments in sequence.
- A pointer to the format string and an index to scan it.
- An integer counter for the number of characters written.
- Small temporary character buffers or constant digit strings for number conversion, if used by the implementation.

This design is simple, memory-efficient, and suited to sequential formatted output. It avoids dynamically allocated lists or arrays because the output can be written as it is processed.

## Instructions

### Compilation

From the project root, run:

```sh
make
```

This should build the static library `libftprintf.a`. Other common Makefile targets are:

```sh
make clean   # Remove object files
make fclean  # Remove object files and the library
make re      # Rebuild from scratch
```

### Usage

Create a separate test file, for example `main.c`:

```c
#include "ft_printf.h"

int main(void)
{
    int count;

    count = ft_printf("Hello %s! Value: %d, hex: %x\n", "42", -42, 255);
    ft_printf("Printed %d characters in the first call.\n", count);
    return (0);
}
```

Compile and run it:

```sh
cc -Wall -Wextra -Werror main.c libftprintf.a -o demo
./demo
```

To validate the project, compare the output **and return values** of `ft_printf` against the system `printf` for each required conversion, including boundary cases such as zero, `INT_MIN`, `UINT_MAX`, empty strings, and null pointers. Note that the representation of a null pointer with `%p` is implementation-dependent (for example, glibc commonly prints `(nil)`).

## Resources

- [`printf(3)` — Linux manual page](https://man7.org/linux/man-pages/man3/printf.3.html): standard formatting behavior and conversion specifications.
- [`stdarg(3)` — Linux manual page](https://man7.org/linux/man-pages/man3/stdarg.3.html): working with variable-length argument lists.
- [`write(2)` — Linux manual page](https://man7.org/linux/man-pages/man2/write.2.html): writing bytes to file descriptors and handling errors.
- [cppreference — `printf` family](https://en.cppreference.com/w/c/io/fprintf): format specifiers, conversions, and return values.
- The **ft_printf project subject** supplied by 42: mandatory project scope and constraints.

### AI usage

AI assistance was used to help explain C concepts, suggest boundary cases, and prepare test programs that compare `ft_printf` with the standard `printf`. It also helped organize and draft this README. The implementation itself should be reviewed and understood by the author; this section should be adjusted to reflect any further AI use in the final submission.
