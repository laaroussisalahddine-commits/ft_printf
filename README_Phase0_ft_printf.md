# Phase 0 — C Foundations & Libft Audit
## ft_printf — 42 / 1337

**Objective:** Repair gaps from Libft before starting `ft_printf`.

This README is a study reference for Phase 0. It explains the concepts, gives compact C examples, shows common mistakes, and includes solutions to the practice exercises. Check the official `ft_printf` subject for the exact required behavior and allowed functions.

---

## Contents

1. [Memory layout](#1-memory-layout)
2. [Pointers, addresses, and dereferencing](#2-pointers-addresses-and-dereferencing)
3. [C integer types](#3-c-integer-types)
4. [Signed/unsigned conversions, overflow, and promotions](#4-signedunsigned-conversions-overflow-and-promotions)
5. [`const`, `static`, scope, and lifetime](#5-const-static-scope-and-lifetime)
6. [`write()`, file descriptors, and return values](#6-write-file-descriptors-and-return-values)
7. [Stack frames, function calls, and recursion](#7-stack-frames-function-calls-and-recursion)
8. [Preprocessing, compilation, assembly, linking, headers, and static libraries](#8-preprocessing-compilation-assembly-linking-headers-and-static-libraries)
9. [Practice solutions](#9-practice-solutions)
10. [Evaluation gate — model answers](#10-evaluation-gate--model-answers)
11. [Quick revision checklist](#11-quick-revision-checklist)

---

## 1. Memory layout

A process's memory layout is an operating-system and toolchain implementation detail. The following is the common conceptual layout for a native C program on Unix-like systems, not a layout guaranteed by the C language.

| Region | Common purpose | Example |
|---|---|---|
| **Text / `.text`** | Machine instructions | Compiled function instructions |
| **`.rodata`** | Read-only constants, often string literals | `"Hello"` |
| **`.data`** | Initialized global and static objects, commonly with nonzero initial values | `int g = 42;` |
| **`.bss`** | Zero-initialized or uninitialized global/static objects | `int g;`, `static int n;` |
| **Stack** | Function-call frames and many automatic local objects | `int local = 3;` |
| **Heap** | Dynamically allocated storage | `malloc(sizeof(int))` |

The compiler, linker, operating system, optimization level, and ABI can change the exact arrangement. Do not infer a variable's region solely from its source syntax on every platform.

### Example

```c
#include <stdlib.h>

int initialized_global = 42;
int zero_global;

static int initialized_static = 7;
static int zero_static;

int main(void)
{
    int local = 3;
    int *ptr = malloc(sizeof *ptr);

    if (ptr != NULL)
    {
        *ptr = 99;
        free(ptr);
    }
    return (0);
}
```

Typical interpretation:

- `initialized_global`: `.data`
- `zero_global`: `.bss`
- `initialized_static`: `.data`
- `zero_static`: `.bss`
- `local`: automatic local variable, commonly stored in a stack frame if not optimized away or kept in a register
- `ptr`: the pointer variable is an automatic local variable; the allocation it points to is dynamically allocated storage (commonly called the heap)
- the memory returned by `malloc`: exists until it is released with `free`, or until the process ends

### String literals and pointers

```c
char *s = "Hello";
```

- `s` is a pointer variable.
- `"Hello"` is a string literal, commonly placed in read-only storage.
- Modifying a string literal is undefined behavior:

```c
/* Do not do this */
s[0] = 'h';
```

If you need a modifiable array:

```c
char s[] = "Hello";
s[0] = 'h';  /* valid: s is a modifiable array */
```

---

## 2. Pointers, addresses, and dereferencing

A pointer is an object whose value refers to an object or function, or is a null pointer. It is not an ordinary integer. Pointer types carry information about the kind of object being pointed to and how pointer arithmetic works.

```c
int x = 42;
int *ptr = &x;
```

| Expression | Meaning | Example value |
|---|---|---|
| `x` | The integer value stored in `x` | `42` |
| `&x` | Address of `x` | An implementation-specific address |
| `ptr` | Pointer value; here it stores the address of `x` | Same address as `&x` |
| `*ptr` | Dereference `ptr`: access the object at the pointed-to address | `42` |

### The `&` and `*` operators

- `&object`: obtains the object's address.
- `*pointer`: dereferences a valid pointer, allowing access to the pointed-to object.
- In a declaration, `int *ptr` means “`ptr` is a pointer to `int`.”
- In an expression, `*ptr = 15` writes `15` into the pointed-to `int`.

### Trace example

```c
int x = 7;
int *ptr = &x;

*ptr = 15;

printf("%d\n", x);       /* 15 */
printf("%d\n", *ptr);    /* 15 */
printf("%p\n", (void *)ptr);
printf("%p\n", (void *)&x);
```

The last two lines print the same pointer value in this example, though the textual representation of a pointer is implementation-defined. `%p` expects a `void *`, so the explicit cast is conventional and portable for object pointers.

### Pointer safety rules

- Do not dereference a null, uninitialized, dangling, or otherwise invalid pointer.
- Check whether `malloc` returned `NULL` before dereferencing its result.
- After `free(ptr)`, do not dereference the freed allocation.
- `free(NULL)` is valid and does nothing.
- A pointer is not guaranteed to fit in `int` or `unsigned int`. Use `%p` to print an object pointer; do not use `%x` as a substitute.
- `sizeof(ptr)` gives the size of the pointer itself, not the size of the pointed-to object.
- `sizeof *ptr` gives the size of the pointed-to type when the expression is valid in that context; `sizeof` does not evaluate its operand except for variable-length array cases.

### `ptr` versus `*ptr` in allocated memory

```c
int *ptr = malloc(sizeof *ptr);
if (ptr != NULL)
{
    *ptr = 20;
    printf("%p\n", (void *)ptr); /* address */
    printf("%d\n", *ptr);        /* 20 */
    free(ptr);
}
```

`ptr` holds the address of the allocation. `*ptr` accesses the integer stored at that address.

---

## 3. C integer types

Exact widths depend on the implementation. Do not assume every machine uses the same size for every type.

| Type | Meaning | Common use |
|---|---|---|
| `char` | Character-sized integer type; plain `char` may be signed or unsigned depending on implementation | Character data and byte storage |
| `signed char` | Small signed integer type | Small signed values |
| `unsigned char` | Small unsigned integer type | Raw bytes and values from `0` to `UCHAR_MAX` |
| `short` / `short int` | Short integer type | Smaller integer ranges |
| `int` | Standard integer type | General integer arithmetic |
| `unsigned int` | Nonnegative integer range with modulo arithmetic | Bit masks, counts, nonnegative values |
| `long`, `long long` | Integer types with at least the standard minimum ranges | Wider integer ranges |
| `size_t` | Unsigned type used for object sizes and `sizeof` results | Sizes and array lengths |
| `ssize_t` | POSIX signed type used by functions such as `read` and `write` for byte counts/errors | Signed byte counts |

`size_t` is defined by standard headers such as `<stddef.h>`; `ssize_t` is POSIX rather than ISO C and is typically declared through headers such as `<sys/types.h>`.

### Format specifiers

For `printf`-family functions, the conversion specifier must match the argument type expected after default argument promotions.

| Type / purpose | Typical format |
|---|---|
| `int` | `%d` or `%i` |
| `unsigned int` | `%u` |
| `unsigned int` in hex | `%x` or `%X` |
| `char` value promoted to `int` | `%c` for character output; `%d` to print its numeric value |
| `void *` | `%p` |
| `size_t` | `%zu` |
| `long` | `%ld` |
| `long long` | `%lld` |
| `unsigned long` | `%lu` |
| `unsigned long long` | `%llu` |
| `ssize_t` | POSIX systems commonly use `%zd` for the corresponding signed-size representation, but follow the platform's documented type/format rules |

A format mismatch can cause undefined behavior. In variadic functions, the compiler generally cannot verify the runtime type of every argument from the format string alone.

### `char` and character codes

```c
char c = 'A';
printf("%c\n", c);  /* A */
printf("%d\n", c);  /* commonly 65 on ASCII-compatible systems */
```

`%c` prints the character corresponding to the promoted integer argument. `%d` prints its integer value. The numeric value `65` assumes an ASCII-compatible execution character set; C does not require ASCII on every implementation.

---

## 4. Signed/unsigned conversions, overflow, and promotions

### Signed and unsigned ranges

For a type with `N` value bits, an unsigned integer type represents `0` through `2^N - 1`. The corresponding signed type's range depends on the C standard version and implementation; on modern conventional systems, `int` is commonly 32 bits with range:

- `INT_MIN = -2147483648`
- `INT_MAX = 2147483647`
- `UINT_MAX = 4294967295`

Use `<limits.h>` rather than hardcoding these values.

```c
#include <limits.h>
printf("%d\n", INT_MIN);
printf("%d\n", INT_MAX);
printf("%u\n", UINT_MAX);
```

### Unsigned arithmetic wraps modulo the range

For an unsigned type, arithmetic is reduced modulo `UINT_MAX + 1`.

```c
unsigned int u = 0;
u = u - 1;
printf("%u\n", u); /* UINT_MAX */
```

This wraparound is defined by C.

### Signed overflow is undefined behavior

```c
int x = INT_MAX;
/* x = x + 1;  Undefined behavior for signed int overflow. */
```

Do not rely on signed overflow wrapping around.

### Why `-INT_MIN` is problematic

On common two's-complement systems, `int` has one more unit of negative range than positive range. For example, `INT_MIN` is `-2147483648`, but `2147483648` cannot fit in a 32-bit `int`. Therefore evaluating `-INT_MIN` cannot be represented as an `int`, causing undefined behavior on those common systems.

To print a signed integer safely, do not negate the minimum value in its signed type. One method is to convert the negative value to `unsigned int` and calculate its magnitude using unsigned arithmetic:

```c
#include <limits.h>
#include <stdio.h>

static void show_magnitude(int n)
{
    unsigned int magnitude;

    if (n < 0)
        magnitude = 0u - (unsigned int)n;
    else
        magnitude = (unsigned int)n;

    printf("%u\n", magnitude);
}
```

This example demonstrates the magnitude calculation; a real printer would emit the digits using division and remainder rather than call `printf`.

### Integer promotions

Types narrower than `int`, such as `char` and `short`, are generally promoted to `int` if `int` can represent all their values; otherwise they are promoted to `unsigned int`.

```c
char c = 'A';
printf("%d\n", c); /* c is promoted before being passed */
```

For variadic functions such as `printf`, default argument promotions apply:

- `char` and `short` are promoted to `int` or `unsigned int`.
- `float` is promoted to `double`.
- `int` remains `int`; `double` remains `double`.

This is why `%c` arguments are retrieved as `int` with `va_arg`, not as `char`.

### Signed/unsigned comparisons

Mixing signed and unsigned values can produce surprising conversions:

```c
int s = -1;
unsigned int u = 1;

if (s < u)
    puts("s is smaller");
else
    puts("comparison is false");
```

On typical systems where `int` and `unsigned int` have the same width, `s` is converted to `unsigned int`, so it becomes `UINT_MAX` and the condition is false. The exact conversion rules depend on the types' ranks and ranges, but the key lesson is to avoid careless signed/unsigned mixing.

---

## 5. `const`, `static`, scope, and lifetime

### `const`

`const` means an object cannot be modified through that particular const-qualified lvalue. It does not automatically mean the object is placed in read-only memory.

```c
const int limit = 10;
/* limit = 20; */ /* constraint violation */
```

Pointer examples:

```c
const char *p1 = "Hello"; /* cannot modify characters through p1 */
char *const p2 = buffer;  /* p2 itself cannot point elsewhere */
const char *const p3 = "Hello"; /* neither p3 nor characters through p3 */
```

### `static`

The meaning depends on where it appears.

```c
static int file_count; /* file scope: internal linkage, static storage duration */

void f(void)
{
    static int calls;  /* block scope: retains value between calls */
    int local = 0;     /* automatic storage duration */
    calls++;
    local++;
}
```

- A file-scope `static` object has internal linkage and static storage duration.
- A block-scope `static` local retains its value between function calls.
- A normal local variable is recreated for each call and has automatic storage duration.
- A function declared `static` at file scope is only directly nameable within that translation unit.

### Scope, linkage, and lifetime are different

- **Scope:** where an identifier can be used by name in source code.
- **Linkage:** whether declarations in different scopes or translation units refer to the same entity.
- **Storage duration / lifetime:** how long the object's storage exists.

Do not treat these as synonyms.

---

## 6. `write()`, file descriptors, and return values

On Unix-like systems, `write` is a POSIX system interface declared in `<unistd.h>`:

```c
ssize_t write(int fd, const void *buf, size_t count);
```

- `fd`: file descriptor.
- `buf`: address of the bytes to write.
- `count`: maximum number of bytes requested.
- Return value: number of bytes actually written, or `-1` on error. A successful call can write fewer bytes than requested.
- `errno` can provide error details after an error, where applicable.

### Standard file descriptors

| Descriptor | Conventional meaning |
|---:|---|
| `0` | Standard input (`stdin`) |
| `1` | Standard output (`stdout`) |
| `2` | Standard error (`stderr`) |

### Example

```c
#include <unistd.h>

int main(void)
{
    write(1, "Hello\n", 6);
    return (0);
}
```

This requests six bytes on standard output.

### Bytes versus visible characters

```c
write(1, "A\0B", 3);
```

This writes three bytes: `A`, NUL, `B`. The NUL byte is not a visible printable character in a typical terminal, but it is still written. `write` uses the explicit byte count; it does not stop at `'\0'`.

For `ft_printf`, this matters for `%c` with `'\0'`: it can output one NUL byte even though the terminal shows no visible glyph. If the call succeeds, that byte contributes to the return count.

### Partial writes and errors

A robust general-purpose write loop handles partial writes and interruptions. A small `ft_printf` implementation must follow its official subject's requirements and expected error behavior; do not assume a single `write` always writes every requested byte.

---

## 7. Stack frames, function calls, and recursion

A function call commonly creates or uses a stack frame containing some combination of parameters, return information, saved registers, and local storage. The exact details are ABI- and compiler-dependent; optimization can keep values in registers or eliminate storage.

```c
int add_one(int n)
{
    int result = n + 1;
    return (result);
}
```

When `add_one(4)` is called:

1. The argument value `4` is passed according to the platform calling convention.
2. The function computes `n + 1`.
3. It returns `5`.
4. Its automatic local objects cease to exist when its execution ends.

### Recursion

A recursive function calls itself. Each active call has its own logical call state.

```c
int factorial(int n)
{
    if (n <= 1)
        return (1);
    return (n * factorial(n - 1));
}
```

For `factorial(4)`, the calls descend through `4`, `3`, `2`, `1`, then results return upward:

```text
factorial(4)
  4 * factorial(3)
      3 * factorial(2)
          2 * factorial(1)
              1
          returns 2
      returns 6
  returns 24
```

The base case prevents infinite recursion. Deep recursion can exhaust available stack resources. In number printers, recursive digit output often works by printing higher-order digits before lower-order digits, but iterative algorithms are also valid.

---

## 8. Preprocessing, compilation, assembly, linking, headers, and static libraries

A simplified toolchain pipeline:

```text
source.c + headers
       |
       v
Preprocessing       (#include, macros, conditional compilation)
       |
       v
Compiler             (C source translated; often includes assembly generation)
       |
       v
Assembler            (assembly -> object file .o)
       |
       v
Linker               (object files + libraries -> executable)
```

The compiler driver (`cc` or `gcc`) usually coordinates multiple stages. Exact internal steps depend on the toolchain and command-line flags.

### Typical commands

Preprocess only:

```sh
cc -E main.c -o main.i
```

Compile to assembly:

```sh
cc -S main.c -o main.s
```

Compile/assemble to an object file:

```sh
cc -Wall -Wextra -Werror -c main.c -o main.o
```

Link object files into an executable:

```sh
cc main.o helper.o -o program
```

Run it:

```sh
./program
```

### Compilation versus linking

- **Compilation/translation:** checks and translates a translation unit into lower-level output, commonly an object file. Some errors, such as syntax errors, are found here.
- **Linking:** combines object files and libraries, resolves external symbol references, and creates an executable or library artifact.
- A program can compile into `.o` files successfully but fail to link because a required function definition is missing.

Example:

```c
/* main.c */
void helper(void);

int main(void)
{
    helper();
    return (0);
}
```

This can compile to `main.o`, but linking without an object/library that defines `helper` normally fails with an undefined-reference error.

### Headers and include guards

A header normally declares interfaces shared across source files:

```c
#ifndef MY_LIB_H
# define MY_LIB_H

int ft_add(int a, int b);

#endif
```

The implementation belongs in a `.c` file:

```c
int ft_add(int a, int b)
{
    return (a + b);
}
```

Include guards prevent repeated inclusion of the same header contents in a translation unit. They do not, by themselves, prevent you from defining the same non-static function in multiple source files.

### Static libraries (`.a`) and `ar`

A static library is an archive of object files; it is not simply a single compiled function. On common Unix-like systems, `ar` creates and updates archives.

```sh
cc -Wall -Wextra -Werror -c ft_add.c -o ft_add.o
ar rcs libftdemo.a ft_add.o
```

- `r`: insert or replace members.
- `c`: create the archive if needed.
- `s`: write/update the symbol index.

Inspect the archive:

```sh
ar t libftdemo.a
nm -s libftdemo.a
file libftdemo.a
```

Link a program against it:

```sh
cc main.o -L. -lftdemo -o program
```

`-L.` searches the current directory for libraries, and `-lftdemo` typically looks for `libftdemo.a` or a suitable shared library according to platform/toolchain rules.

### Makefile basics

```make
NAME = program
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c ft_add.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

The command lines under targets must begin with a literal tab in a conventional Makefile.

Common automatic variables:

- `$@`: target name.
- `$<`: first prerequisite.
- `$^`: all prerequisites.

For `ft_printf`, follow the exact target names, library archive requirements, source lists, and allowed compiler flags in the official subject.

---

## 9. Practice solutions

### 9.1 Predict 15 C outputs

Assume each snippet is independent, uses a conventional ASCII-compatible environment where relevant, and has the required headers. Outputs described as implementation-dependent are marked.

#### Q1 — Basic integer

```c
int x = 7;
printf("%d\n", x);
```

Output:
```text
7
```

#### Q2 — Character as character and integer

```c
char c = 'A';
printf("%c %d\n", c, c);
```

Typical ASCII-compatible output:
```text
A 65
```

The character argument is promoted before the call. The numeric code `65` assumes ASCII compatibility.

#### Q3 — Pointer dereference

```c
int x = 7;
int *p = &x;
*p = 12;
printf("%d\n", x);
```

Output:
```text
12
```

#### Q4 — Static local lifetime

```c
void f(void)
{
    static int n;
    n++;
    printf("%d\n", n);
}
```

If called three times, output:
```text
1
2
3
```

#### Q5 — Automatic local initialization

```c
int x;
printf("%d\n", x);
```

There is no valid predictable output: reading the uninitialized automatic `int` produces undefined behavior in C versions commonly used for 42 work. Do not use this as a test of a particular numeric value.

#### Q6 — Unsigned wraparound

```c
unsigned int u = 0;
u--;
printf("%u\n", u);
```

Output:
```text
UINT_MAX
```

Its decimal value depends on the width of `unsigned int`.

#### Q7 — Signed overflow

```c
int x = INT_MAX;
/* x++; */
```

As written, the increment is commented out, so this snippet alone doesn't increment `x`. If `x++` were executed, signed overflow would be undefined behavior.

#### Q8 — Array indexing

```c
int a[] = {10, 20, 30};
printf("%d\n", a[1]);
```

Output:
```text
20
```

#### Q9 — `sizeof` an array in its defining scope

```c
int a[] = {10, 20, 30};
printf("%zu\n", sizeof(a) / sizeof(a[0]));
```

Output:
```text
3
```

Here `sizeof(a)` measures the entire array. When passed as a function parameter, an array parameter is adjusted to a pointer type, so the same technique does not work there.

#### Q10 — Function return

```c
int add(int a, int b) { return (a + b); }
printf("%d\n", add(2, 3));
```

Output:
```text
5
```

#### Q11 — Recursion

```c
int f(int n)
{
    if (n == 0)
        return (0);
    return (1 + f(n - 1));
}
printf("%d\n", f(4));
```

Output:
```text
4
```

#### Q12 — String literal

```c
char *s = "Hello";
printf("%s\n", s);
```

Output:
```text
Hello
```

The pointer can point to the literal, but modifying the literal is undefined behavior.

#### Q13 — NUL byte written by `write`

```c
write(1, "A\0B", 3);
```

Three bytes are written: `A`, NUL, `B`. A terminal may visually show only `A` and possibly effects of `B` depending on how the output is inspected; the byte sequence is what matters.

#### Q14 — `sizeof` pointer

```c
int x = 1;
int *p = &x;
printf("%zu\n", sizeof(p));
```

Output is `sizeof(int *)`, commonly 8 on a 64-bit system, but the exact size is implementation-dependent. It is not the size of `x`.

#### Q15 — Compilation versus linking

`main.c` calls a declared `helper()` whose definition is absent from every linked object and library.

- Compilation of `main.c` to `main.o` can succeed.
- Linking a normal executable will fail because the external definition of `helper` cannot be resolved.

---

### 9.2 Algorithm for a signed decimal printer

Goal: print an `int` in decimal without negating `INT_MIN` in the signed type.

Algorithm:

1. If `n < 0`, write `'-'`.
2. Compute the magnitude using unsigned arithmetic, not `-n` in type `int`.
3. If the magnitude is at least 10, process the quotient by 10 first.
4. Print the last digit using remainder `% 10`, converted to `'0' + digit`.
5. Handle zero explicitly, because a loop conditioned on `n > 0` otherwise prints nothing for zero.

Safe magnitude calculation:

```c
unsigned int magnitude;

if (n < 0)
    magnitude = 0u - (unsigned int)n;
else
    magnitude = (unsigned int)n;
```

Why this works on conventional implementations: converting a negative signed integer to the corresponding unsigned type is defined modulo one more than the maximum unsigned value. Subtracting that converted value from zero in unsigned arithmetic yields the magnitude, including for `INT_MIN`.

Pseudocode for recursive digit order:

```text
print_unsigned_decimal(magnitude):
    if magnitude >= 10:
        print_unsigned_decimal(magnitude / 10)
    print_character('0' + magnitude % 10)
```

This is pseudocode, not a complete `ft_printf` solution. For an actual implementation, ensure every `write` result and returned byte count is handled according to the assignment's requirements.

### 9.3 Algorithm for an unsigned decimal printer

```text
print_unsigned_decimal(n):
    if n >= 10:
        print_unsigned_decimal(n / 10)
    print_character('0' + n % 10)
```

For `n == 0`, this pseudocode prints `0` because the final digit operation still executes. For `n == 429`, recursive calls process `42`, then `4`, and output occurs while the calls return: `429`.

### 9.4 Print `INT_MIN` without signed overflow

The critical rule is: never compute `-n` while `n` is `INT_MIN` in type `int`.

Use the unsigned magnitude algorithm above, then print the magnitude's digits. The sign is printed separately. This also handles ordinary negative values and zero.

### 9.5 Trace variable addresses and lifetimes

```c
int global_value = 10;

int main(void)
{
    int local_value = 20;
    int *ptr = &local_value;
    /* inspect global_value, local_value, ptr, *ptr here */
}
```

Expected conceptual facts:

- `global_value`: static storage duration, commonly `.data`.
- `local_value`: automatic storage duration, commonly associated with the stack frame.
- `ptr`: automatic pointer variable, commonly associated with the stack frame.
- `*ptr`: the value of `local_value`, initially `20`.
- `&local_value`: the address of `local_value`.
- `ptr == &local_value`: true.
- The exact printed addresses cannot be predicted in advance and can change between executions due to ASLR and other implementation details.

### 9.6 Build a small `.a` file manually

Given `ft_add.c`:

```c
int ft_add(int a, int b)
{
    return (a + b);
}
```

Commands:

```sh
cc -Wall -Wextra -Werror -c ft_add.c -o ft_add.o
ar rcs libftdemo.a ft_add.o
ar t libftdemo.a
nm -s libftdemo.a
```

Expected checks:

- `ft_add.o` exists.
- `libftdemo.a` exists.
- `ar t` lists `ft_add.o`.
- `nm` shows the exported `ft_add` symbol, with symbol-letter details depending on platform.

### 9.7 Debug a deliberately broken program

Broken code:

```c
#include <stdlib.h>

int main(void)
{
    int *ptr = malloc(sizeof *ptr);
    *ptr = 42;
    free(ptr);
    return (*ptr);
}
```

Problems:

1. It doesn't check whether `malloc` returned `NULL` before dereferencing.
2. It dereferences `ptr` after `free(ptr)`, which is use-after-free and undefined behavior.

Correct reasoning:

1. Check `ptr != NULL`.
2. Write and read the allocation only while it is alive.
3. Save any value needed after `free` into a separate integer before freeing.
4. Never dereference the freed pointer.

Example of the corrected structure:

```c
#include <stdlib.h>

int main(void)
{
    int *ptr = malloc(sizeof *ptr);
    int value;

    if (ptr == NULL)
        return (1);
    *ptr = 42;
    value = *ptr;
    free(ptr);
    return (value == 42 ? 0 : 1);
}
```

---

## 10. Evaluation gate — model answers

### Why is `-INT_MIN` problematic?

On common two's-complement systems, the negative range has one extra magnitude compared with the positive range. `INT_MIN` has no representable positive counterpart in the same signed `int` type, so negating it causes signed overflow and undefined behavior. Use unsigned magnitude arithmetic instead.

### Why is a pointer not an ordinary integer?

A pointer represents an address/reference to an object or function, or a null pointer. Its type controls dereferencing and pointer arithmetic. Its size and representation are implementation-dependent; it is not guaranteed to fit in `int` or `unsigned int`. Use pointer-aware operations and `%p` for printing object pointers.

### What is the difference between compilation and linking?

Compilation translates each source translation unit into a lower-level representation, often an object file. Linking combines object files and libraries and resolves external symbol references. A source file can compile successfully but the final executable can fail to link if a referenced function definition is missing.

### What does `write()` return?

On success, the number of bytes actually written, which can be less than requested. On error, it returns `-1` and sets `errno` where applicable. Its return type is `ssize_t` on POSIX systems.

### Why does `%c` use `va_arg(args, int)`?

The default argument promotions convert `char` and `short` arguments to `int` or `unsigned int` before passing them through `...`. For `%c`, the expected argument type is `int`, so `va_arg(args, int)` is used.

### Why can `ft_printf("%c", '\0')` write one byte?

The character value is passed as an integer after promotion. The `%c` conversion writes the corresponding byte; NUL is a byte even though it is not normally visible as a terminal glyph. A successful one-byte output contributes one to the return count.

---

## 11. Quick revision checklist

Before moving to Phase 1, you should be able to explain these without copying the README:

- [ ] Difference between `.data` and `.bss`.
- [ ] Difference between a pointer's value (`ptr`), its target (`*ptr`), and an object's address (`&x`).
- [ ] Why string literals must not be modified.
- [ ] Difference between `size_t` and `ssize_t`.
- [ ] Why unsigned wraparound is defined but signed overflow is not.
- [ ] Why `-INT_MIN` is unsafe and how unsigned magnitude avoids it.
- [ ] Why `char` is promoted to `int` for variadic calls in common cases.
- [ ] Difference between scope, linkage, and storage duration.
- [ ] What `write()` returns and what file descriptors 0, 1, and 2 mean.
- [ ] How recursive calls return and why a base case is needed.
- [ ] Difference between preprocessing, compilation, assembly, and linking.
- [ ] How to create and inspect a `.a` archive with `ar` and `nm`.
- [ ] How to recognize an undefined reference and a use-after-free.
- [ ] How to explain each practice solution and identify the behavior that is implementation-dependent or undefined.

**Phase 0 completion rule:** Do not move on merely because the examples compile. Move on when you can explain the rules, predict defined outputs, recognize undefined behavior, and recreate the algorithms independently.
