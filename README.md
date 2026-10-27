# ft_printf — Deep Mastery Roadmap (42 / 1337)

> **Goal:** Understand, build, test, debug, and defend `ft_printf` independently — not just pass a tester.

This is a **theory + practice + evaluation** roadmap for a student moving from **Libft** to **ft_printf** at 42 Network / 1337. It develops C fundamentals, variadic functions, format parsing, printing algorithms, debugging, build systems, and peer-evaluation skills.

**Important:** Always use the `ft_printf` subject available in your intra as the source of truth for allowed functions, bonus requirements, file names, and expected behavior. The accompanying PDF used while preparing this roadmap was a **Libft** subject, not the `ft_printf` subject.

## How to use this roadmap

For **every topic**:

1. **Theory:** Explain the concept from first principles.
2. **Visualize:** Draw the relevant memory layout, execution trace, or algorithm.
3. **Predict:** Write the expected output and return value *before* running code.
4. **Practice:** Implement a small standalone exercise without copying a full `ft_printf` solution.
5. **Test:** Include normal, boundary, and failure cases.
6. **Debug:** Deliberately break an example and explain the cause.
7. **Defend:** Answer evaluation-style questions and reimplement from memory.

**Progress rule:** A level is complete only when you can explain *why* your code works, not merely when tests pass.

## Progress tracker

- [ ] Phase 0 — C foundations and Libft audit
- [ ] Phase 1 — `printf` and format strings
- [ ] Phase 2 — Variadic functions
- [ ] Phase 3 — `write()`, bytes and errors
- [ ] Phase 4 — Number representation and conversions
- [ ] Phase 5 — Pointers and memory representation
- [ ] Phase 6 — Independent printers
- [ ] Phase 7 — Parser, dispatcher, architecture
- [ ] Phase 8 — Undefined behavior and edge cases
- [ ] Phase 9 — Makefile, compilation and linking
- [ ] Phase 10 — Moulinette-style testing
- [ ] Phase 11 — Bonus formatting (if applicable)
- [ ] Phase 12 — 42 defense simulation

---

## Phase 0 — C Foundations & Libft Audit

**Objective:** Repair gaps from Libft before starting `ft_printf`.

### Theory

- Stack, heap, `.rodata`, `.data`, `.bss`.
- Pointers vs addresses vs dereferenced values.
- `char`, `int`, `unsigned int`, `size_t`, `ssize_t`.
- Signed/unsigned conversions, overflow, integer promotions.
- `const`, `static`, scope and lifetime.
- `write()`, file descriptors and return values.
- Stack frames, function calls and recursion.
- Preprocessing, compilation, assembly, linking, headers, static libraries.

### Practice

- [ ] Predict 15 C outputs without running them.
- [ ] Write signed and unsigned number printers.
- [ ] Print `INT_MIN` without signed overflow.
- [ ] Trace variable addresses and lifetimes.
- [ ] Build a small `.a` file manually using `ar`.
- [ ] Debug a deliberately broken C program.

**Evaluation gate:** Explain why `-INT_MIN` is problematic, why a pointer is not an ordinary integer, and the difference between compilation and linking.

## Phase 1 — Understanding `printf` & Format Strings

**Objective:** Understand the job of `printf` before implementing it.

### Theory

- Output bytes vs the return value.
- Format strings, normal characters and `%`.
- Conversion specifiers vs their arguments.
- Parsing, tokens and simple state machines.
- Interpretation of `printf("A%dB", 42)`.

### Practice

- [ ] Write a character-by-character string scanner.
- [ ] Detect `%`, `%%` and supported conversion characters.
- [ ] Calculate printed byte counts by hand.
- [ ] Trace format indices on paper.
- [ ] Classify supported, unsupported and incomplete formats.

**Evaluation gate:** Explain the parser with a diagram without reading the source code.

## Phase 2 — Variadic Functions: Deep Dive

**Objective:** Understand `...` and `<stdarg.h>` beyond memorizing syntax.

### Theory

- Fixed arguments vs variadic arguments.
- `va_list`, `va_start`, `va_arg`, `va_end`, `va_copy`.
- Default argument promotions (`char`/`short` to `int` in typical cases; `float` to `double`).
- Why `va_arg` must retrieve the expected promoted type.
- What a compiler does and does not know about variadic argument types.
- Register/stack passing conventions and platform-dependent ABI internals.
- Mismatched retrieval types and undefined behavior.

### Practice

- [ ] Implement `sum(int count, ...)`.
- [ ] Read a documented sequence of `int` and `char *` arguments.
- [ ] Demonstrate proper `va_copy` use.
- [ ] Examine assembly for a small variadic function (optional advanced work).
- [ ] Trace exactly which `va_arg` is called at each conversion.

**Evaluation gate:** Explain why `%c` requires `va_arg(args, int)` rather than `char`.

## Phase 3 — `write()`, Bytes & Error Handling

**Objective:** Know what happens when output is written.

### Theory

- File descriptors 0, 1 and 2.
- `write(fd, buffer, count)`.
- Visible characters vs actual bytes.
- Embedded `\0`, newline and escape sequences.
- Partial writes, interrupted writes and errors.
- `ssize_t`, `-1`, `errno`, `EBADF`, `EPIPE`.

### Practice

- [ ] Print a NUL byte and inspect output as bytes.
- [ ] Redirect stdout to a file and inspect its contents.
- [ ] Write a byte-output helper and reason about its return value.
- [ ] Test an invalid descriptor.
- [ ] Simulate a write failure with a test harness.

**Evaluation gate:** Explain why `ft_printf("%c", '\0')` prints one byte even though it displays nothing visibly.

## Phase 4 — Number Representation & Conversion

**Objective:** Convert numerical values to textual representations correctly.

### Theory

- Binary, decimal and hexadecimal.
- Base conversion with division and remainder.
- ASCII digit mapping.
- Signed vs unsigned arithmetic.
- Two's complement (common representation) and integer limits.
- `INT_MIN`, `INT_MAX`, `UINT_MAX`.
- `uintptr_t` and `<stdint.h>`.
- Recursive vs iterative digit printers.

### Practice

- [ ] Implement `print_base_unsigned(n, base)`.
- [ ] Implement signed decimal printing.
- [ ] Implement lower- and uppercase hexadecimal.
- [ ] Diagram recursive calls and their output order.
- [ ] Convert several values manually between bases.
- [ ] Verify output bytes and character counts.

**Evaluation gate:** Explain why decimal 255 becomes hexadecimal `ff`.

## Phase 5 — Pointers & Memory Representation

**Objective:** Understand `%p` from address to formatted output.

### Theory

- Memory addresses, pointer types and `void *`.
- `sizeof(void *)` and integer width.
- Stack vs heap addresses.
- Address Space Layout Randomization (ASLR).
- Pointer-to-integer conversions when a suitable integer type exists.
- Why `%p` differs from `%x`.
- NULL-pointer formatting can vary by environment.

### Practice

- [ ] Print an address of a local variable.
- [ ] Print an address returned by `malloc`.
- [ ] Compare `%p` results with the target libc.
- [ ] Test a NULL pointer.
- [ ] Inspect addresses with a debugger.
- [ ] Experiment with `sizeof(void *)`.

**Evaluation gate:** Explain why `%p` retrieves a `void *` and why `unsigned int` may not hold a pointer value.

## Phase 6 — Independent Printers

**Objective:** Build one independently testable printer per required output category.

| Conversion | Printer responsibility | Important cases |
|---|---|---|
| `%c` | Character byte | `\0`, argument promotion |
| `%s` | String bytes | Empty string, NULL behavior |
| `%d`, `%i` | Signed decimal | Negative values, `INT_MIN` |
| `%u` | Unsigned decimal | Zero, `UINT_MAX` |
| `%x`, `%X` | Hexadecimal | Zero, letter case |
| `%p` | Pointer | Address width, NULL |
| `%%` | Literal `%` | Consumes no variadic argument |

For **each** category:

- [ ] Explain the algorithm in your own words.
- [ ] Predict output and return values.
- [ ] Implement from scratch.
- [ ] Test boundaries and special cases.
- [ ] Introduce a bug and diagnose it.
- [ ] Explain each line of your code.

**Evaluation gate:** Recreate each printer from a blank file and justify design decisions.

## Phase 7 — Parser, Dispatcher & Architecture

**Objective:** Combine components using a clear division of responsibilities.

```text
ft_printf(format, ...)
        |
        v
     parser
     /    \
normal    conversion
  |          |
write     dispatcher
  |          |
  |       va_arg + printer
  \          /
   \        /
    byte count / error state
             |
             v
          return
```

### Theory

- Separation of concerns.
- Parsing vs dispatching vs printing.
- Single-responsibility helpers.
- Passing `va_list` safely between functions.
- Error propagation and byte-count accumulation.
- Format indices and off-by-one errors.
- Extensible architecture.

### Practice

- [ ] Implement plain-text output first.
- [ ] Add one conversion at a time.
- [ ] Create a conversion dispatcher.
- [ ] Integrate all required conversions.
- [ ] Trace the parser, arguments and return count.
- [ ] Refactor without breaking previous behavior.

**Evaluation gate:** Explain the call flow and modify one printer without rewriting the parser.

## Phase 8 — Undefined Behavior & Edge Cases

**Objective:** Distinguish bugs, undefined behavior and implementation-specific behavior.

### Topics

- NULL format pointers.
- Unsupported conversion characters and trailing `%`.
- Wrong variadic argument types or missing arguments.
- Invalid pointers.
- Empty strings and embedded NUL bytes.
- Zero and integer boundaries.
- Return-value overflow.
- Differences between libc environments.

### Practice

- [ ] Build a boundary-value suite.
- [ ] Label tests as defined, undefined or implementation-specific.
- [ ] Debug crashes using GDB or LLDB.
- [ ] Try AddressSanitizer and UndefinedBehaviorSanitizer.
- [ ] Use Valgrind if available.

**Evaluation gate:** Explain why behavior observed for an undefined case does **not** establish a portable requirement.

## Phase 9 — Makefile, Header, Compilation & Linking

**Objective:** Understand and defend the entire build system.

### Theory

- `.c` → `.o` → `.a` → executable.
- Compilation vs linking.
- Archives and `ar rcs`.
- Symbol tables and `nm`.
- Object inspection using `file` and `objdump`.
- Header guards.
- Build dependencies.
- Make automatic variables: `$@`, `$<`, `$^`.
- Incremental builds and unnecessary relinking.

### Practice

- [ ] Build your archive manually.
- [ ] Write a Makefile respecting your official subject.
- [ ] Delete one `.o` and predict the rebuild.
- [ ] Change one `.c` and observe what rebuilds.
- [ ] Deliberately introduce undefined references.
- [ ] Debug a missing symbol.
- [ ] Verify `make`, `clean`, `fclean` and `re`.

**Evaluation gate:** Explain every important Makefile line and the difference between compilation and symbol resolution.

## Phase 10 — Test Like Moulinette

**Objective:** Own your test suite rather than trusting only third-party testers.

| Test family | What it proves |
|---|---|
| Unit tests | Each printer works alone |
| Integration tests | Mixed conversions work together |
| Differential tests | Defined cases match libc output and returns |
| Boundary tests | Integer limits, zero, NULL, NUL |
| Failure tests | Error handling and propagation |
| Build tests | Makefile, Norm, symbols |
| Regression tests | Old features still work after changes |

### Practice

- [ ] Create a personal `test_printf.c`.
- [ ] Capture stdout as **bytes**, not just displayed text.
- [ ] Compare stdout and return values for defined cases.
- [ ] Test redirection.
- [ ] Automate test execution in a shell script.
- [ ] Maintain a bug log containing root cause, fix and regression test.

**Evaluation gate:** Diagnose a failed test without immediately consulting a complete solution.

## Phase 11 — Bonus: Advanced Formatting

> Start only when mandatory behavior is solid. Confirm the exact bonus syntax and requirements from your own subject.

### Theory

- Flags: `-`, `0`, `#`, `+` and space.
- Field width.
- Precision (`.`).
- Padding and alignment.
- Interaction between signs, prefixes, padding and precision.
- Parsing conversion metadata into a structure.

### Practice

- [ ] Build an independent flags parser.
- [ ] Represent conversion options in a `struct`.
- [ ] Implement padding separately.
- [ ] Compare supported flag combinations with libc.
- [ ] Test conflicting or interacting options.
- [ ] Re-run mandatory regression tests.

**Evaluation gate:** Add or modify a formatting behavior without destabilizing basic conversions.

## Phase 12 — 42 Defense Simulation

**Objective:** Defend the implementation and make small changes independently.

- [ ] Explain each file and function.
- [ ] Trace `va_list` through a mixed format.
- [ ] Predict exact output **and** return value.
- [ ] Identify a bug in an unfamiliar implementation.
- [ ] Reconstruct a helper after it is removed.
- [ ] Recognize undefined behavior.
- [ ] Diagnose a segfault or incorrect return count.
- [ ] Perform a small modification while preserving other features.
- [ ] Rebuild essential components from an empty file.
- [ ] Explain Makefile, headers, linking and testing decisions.

**Final pass condition:** Correct behavior, clear explanations, and independent debugging/modification.

---

## Starter diagnostic — Question 1

Predict the following **before** compiling:

```c
#include <stdio.h>

void test(char c)
{
    printf("%d\n", c);
}

int main(void)
{
    char x = 'A';
    test(x);
    return (0);
}
```

**Questions:**

1. What is printed?
2. Why does `%d` print that value instead of `A`?
3. Does `x` permanently change from `char` to `int`, or is a conversion involved when calling the function / passing an argument to `printf`?

## Reference material

- Your **official** `ft_printf` subject on the 42 intranet.
- `man 3 printf`
- `man 3 stdarg`
- `man 2 write`
- `man 3 malloc`
- `man 3 free`
- Your own completed Libft and its tests.

## Learning agreement

AI, documentation and peer discussions can help explain concepts, propose tests and review reasoning. The algorithms, code, debugging decisions, and evaluation explanations should be developed independently.

**Final rule:** Don't move to the next phase just because the code works. Move forward when you can clearly explain **why** it works.
