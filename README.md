*This project has been created as part of the 42 curriculum by danicort.*

# push_swap

## Description
push_swap sorts a list of unique integers using only two stacks (A and B)
and a restricted set of operations. The program must output a sequence of
allowed operations (one per line) that, when applied to the initial stack A,
results in A sorted in ascending order. The goal is to produce as few
instructions as possible.

## Instructions

Requirements: a C compiler (gcc/clang), `make`, and the Norminette for
style checking if you want to validate the project locally.

Build:

```bash
make
```

Run:

```bash
./push_swap 3 2 1
# or
./push_swap "3 2 1"
```

The program prints the operations to stdout (one per line). If the input is
invalid (non-integer token, duplicates, out-of-range), the program writes
"Error\n" to stderr and exits with status 1.

Bonus (checker):

```bash
make bonus
# Nota: `make bonus` compila apenas o `checker`.
# Para compilar os dois binários, rode:
make && make bonus

./push_swap 3 2 1 | ./checker 3 2 1
```

## Project structure

This repository uses a common 42 layout:

- includes/ — public headers (project API)
- src/ — push_swap core (commands + sorting algorithm)
- utils/ — parsing + stack helpers shared by push_swap/checker
- bonus/ — checker sources (bonus target)
- libft/ — minimal libft used by the project
- test_performance.sh — benchmark + correctness script

Key entry points:

- src/main.c — entry point and orchestration
- includes/push_swap.h — public structs and prototypes
- src/cmd_*.c — implementations of the allowed operations
- src/turk_*.c — sorting algorithm (Turk)
- utils/stack_*.c + utils/parse_helpers.c — parsing and stack helpers

## Norminette / Coding standard

This repository follows 42's Norminette style rules. Key rules followed:

- 42 header in every file
- tabs for indentation
- functions kept short (<= 25 lines) when practical
- avoid global variables

To run the style checker locally:

```bash
norminette .
```

## Tests and quick checks

Build the project:

```bash
make
```

Build the checker (bonus):

```bash
make bonus
# `make bonus` compila apenas o `checker`.
```

Use the checker manually:

```bash
ARG="3 2 1";
./push_swap $ARG | ./checker $ARG
```

Run the benchmark/correctness script:

```bash
chmod +x test_performance.sh
./test_performance.sh
```

Run quick examples:

```bash
./push_swap 2 1
# expected (one valid output):
# sa

./push_swap 1 2 3
# no output (already sorted)
```

## Notes

- If you use `libft` functions, include their sources in a `libft` folder and
  ensure the Makefile builds the library.

- Build artifacts are not tracked: binaries (`push_swap`, `checker`) and
  objects under `objs/` (including `objs/libft/`).

## Author

danicort — student at 42 (local repository maintenance and refactor)

## Resources

Classic references:

- push_swap subject (42 intranet) — project rules and benchmarks
- Norminette — 42 style checker
- C standard library documentation (man pages)

