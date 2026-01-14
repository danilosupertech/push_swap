# push_swap

*A 42 school project by danicort*

## Overview

**push_swap** is a sorting algorithm project that sorts integers using two stacks and a limited set of operations. The goal is to produce the shortest sequence of operations to sort stack A in ascending order while keeping stack B empty.

This implementation uses the **Turk algorithm**, a cost-based greedy strategy that picks the cheapest move at each step by computing rotation and push costs.

## Requirements

- **C compiler**: `gcc` or `clang`
- **Make**: To build the project
- **Norminette**: For code style validation (optional, for 42 evaluation)

## Building

### Main program
```bash
make
```

### Clean
```bash
make clean      # Remove object files
make fclean     # Remove object files and binaries
make re         # Full rebuild
```

## Usage

### Basic usage
```bash
./push_swap 3 2 1
./push_swap "3 2 1"
./push_swap 42 -5 100 0
```

## Allowed Operations

| Operation | Effect |
|-----------|--------|
| `sa` | Swap first 2 elements of stack A |
| `sb` | Swap first 2 elements of stack B |
| `ss` | Swap both stacks simultaneously |
| `pa` | Push top element from B to A |
| `pb` | Push top element from A to B |
| `ra` | Rotate stack A (move first to last) |
| `rb` | Rotate stack B (move first to last) |
| `rr` | Rotate both stacks |
| `rra` | Reverse rotate A (move last to first) |
| `rrb` | Reverse rotate B (move last to first) |
| `rrr` | Reverse rotate both stacks |

## Error Handling

The program outputs `Error\n` to stderr and exits with status 1 if:
- Input contains non-integer tokens
- Input contains duplicate values
- Integer values overflow long range
- Allocation fails

Otherwise exits with status 0 on success.

## Project Structure

```
push_swap/
├── Makefile                 # Build configuration
├── README.md               # This file
├── includes/
│   └── push_swap.h         # Main header (data structures, prototypes)
├── src/
│   ├── main.c              # Entry point and orchestration
│   ├── commands/           # Basic stack operations
│   │   ├── swap_ops.c      # sa, sb, ss
│   │   ├── push_ops.c      # pa, pb
│   │   ├── rotate_ops.c    # ra, rb, rr
│   │   └── rev_rotate_ops.c # rra, rrb, rrr
│   ├── algorithm/          # Turk sorting algorithm
│   │   ├── turk_sort.c     # Main orchestration
│   │   ├── small_cases.c   # Sort 2-3 elements
│   │   ├── final_rotation.c # Position minimum on top
│   │   ├── init_nodes.c    # Initialize node metadata
│   │   ├── find_targets.c  # Find target positions
│   │   ├── calc_costs.c    # Calculate movement costs
│   │   ├── execute_moves.c # Execute optimal moves
│   │   └── rotation_moves.c # Combined rotations helpers
│   ├── parsing/            # Input validation and parsing
│   │   ├── input_to_stack.c # Main parsing orchestration
│   │   ├── parse_validate.c # Integer validation
│   │   └── parse_split_free.c # Free helper for split arrays
│   └── stack/              # Stack utilities
│       ├── stack_nav.c     # Navigation (length, find last)
│       ├── stack_order.c   # Order analysis (sorted, min, max)
│       └── stack_ops.c     # Memory management (append, free)
└── libft/                  # Custom C library
    ├── Makefile            # Libft build configuration
    ├── libft.h             # Libft header
    ├── ft_atol.c           # String to long conversion
    ├── ft_bzero.c          # Zero memory block
    ├── ft_calloc.c         # Allocate and zero memory
    ├── ft_isdigit.c        # Check if character is digit
    ├── ft_putstr_fd.c      # Write string to file descriptor
    ├── ft_split.c          # Split string by delimiter
    ├── ft_strdup.c         # Duplicate string
    ├── ft_strlen.c         # Calculate string length
    ├── ft_strncmp.c        # Compare strings (n bytes)
    └── ft_substr.c         # Extract substring
```

## Algorithm Details

### Commands Module
The **commands/** folder implements the 11 basic stack operations mandated by the subject:

- **swap_ops.c**: Implements `sa` (swap first 2 of A), `sb` (swap first 2 of B), and `ss` (swap both)
- **push_ops.c**: Implements `pa` (push top of B to A) and `pb` (push top of A to B)
- **rotate_ops.c**: Implements `ra` (rotate A up), `rb` (rotate B up), and `rr` (rotate both)
- **rev_rotate_ops.c**: Implements `rra` (rotate A down), `rrb` (rotate B down), and `rrr` (rotate both down)

All operations run in **O(1) time** by only manipulating top/bottom node pointers. Each operation prints its name to stdout when executed.

### Parsing Module
The **parsing/** folder handles input validation and stack initialization:

- **input_to_stack.c**: Main entry point that orchestrates parsing flow
  - Handles both single string and multiple argument formats
  - Calls validation and builds the initial stack A
- **parse_validate.c**: Validates each token
  - Checks for valid integer format (with optional +/- signs)
  - Converts strings to integers using `ft_atol`
  - Detects overflow beyond `int` range
  - Checks for duplicate values
- **parse_split_free.c**: Memory management for split strings
  - Frees dynamically allocated string arrays after parsing

If any validation fails, outputs `Error\n` to stderr and exits with status 1.

### Stack Module
The **stack/** folder provides core stack manipulation utilities:

- **stack_ops.c**: Memory management
  - `stack_new()`: Creates new stack nodes
  - `stack_add_back()`: Appends nodes to stack end
  - `free_stack()`: Frees all nodes in a stack
- **stack_nav.c**: Navigation functions
  - `stack_len()`: Returns number of nodes
  - `find_last()`: Returns pointer to last node
- **stack_order.c**: Analysis functions
  - `stack_sorted()`: Checks if stack is already sorted
  - `find_min()`: Finds node with minimum value
  - `find_max()`: Finds node with maximum value

These utilities support both doubly-linked list operations and the algorithm's decision-making process.

### Turk Algorithm
The Turk algorithm uses a cost-based greedy approach:

1. **Initialization**: Calculate positions and target positions for each element
2. **Cost Calculation**: For each element in stack A, calculate the cost to:
   - Move it to the top of A
   - Find its target position in B
   - Move it to that target
   - Position the receiver element optimally
3. **Selection**: Choose the cheapest move
4. **Execution**: Perform optimal combined rotations
5. **Completion**: Repeat until A is sorted and B is empty
6. **Final Rotation**: Rotate A so the smallest element is on top

### Performance

Expected results for typical inputs:
- **3 numbers**: ≤ 3 operations
- **5 numbers**: ≤ 12 operations
- **100 numbers**: < 700 operations (target: 500-600)
- **500 numbers**: < 5500 operations (target: 4900-5200)

These limits align with 42 evaluation requirements for maximum score.

## Testing Examples

### Basic functionality
```bash
# Test with simple input
./push_swap 3 2 1
# Output: sa, ra (or similar short sequence)

# Test with already sorted stack
./push_swap 1 2 3
# Output: (empty - no operations needed)

# Test with reverse sorted
./push_swap 5 4 3 2 1
```

### Count operations
```bash
# Small set (3 numbers) - should use ≤ 3 operations
./push_swap 2 1 3 | wc -l

# Medium set (5 numbers) - should use ≤ 12 operations
./push_swap 5 4 3 2 1 | wc -l

# Large set (100 numbers) - should use < 700 operations
ARG=$(shuf -i 1-1000 -n 100 | tr '\n' ' '); ./push_swap $ARG | wc -l
```

### Validate with checker
```bash
# If you have checker program
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG
# Expected output: OK

# Test with invalid input
./push_swap 1 2 3 2
# Expected output: Error
```

### Memory leak detection
```bash
# Install valgrind (Ubuntu/WSL)
sudo apt-get install valgrind

# Basic memory check
valgrind --leak-check=full ./push_swap 9 0 -217 2147483647 -2147483648
# Expected: "All heap blocks were freed -- no leaks are possible"

# Test with invalid input (should still free memory)
valgrind --leak-check=full ./push_swap 1 2 3 abc
# Expected: Error + no leaks

# Test with duplicates
valgrind --leak-check=full ./push_swap 5 2 3 5 1
# Expected: Error + no leaks

# Test with large input
valgrind --leak-check=full ./push_swap $(shuf -i 1-500 -n 100 | tr '\n' ' ')
# Expected: no leaks

# Detailed memory report
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./push_swap 4 2 1 3
# Shows detailed memory allocation info

# Test with empty/single argument
valgrind --leak-check=full ./push_swap ""
valgrind --leak-check=full ./push_swap 42
# Expected: no operations, no leaks
```

## Code Style

This project follows **42 Norminette** standards:
- 42 header comment in every file
- Tab indentation
- Functions ≤ 25 lines (when practical)
- No global variables
- Clear function documentation

To validate locally:
```bash
norminette .
```

## Data Structures

### Stack Node
```c
typedef struct s_stack
{
	int			value;        // Stored integer
	int			index;        // Normalized index (0..n-1)
	int			push_cost;    // Calculated move cost
	bool		above_median; // Position hint (top/bottom)
	bool		cheapest;     // Flag for chosen move
	struct s_stack	*target_node; // Target counterpart
	struct s_stack	*next;        // Next node
	struct s_stack	*prev;        // Prev node
} t_stack;
```

## Key Files Reference

| File | Purpose |
|------|---------|
| `includes/push_swap.h` | Data structures and function prototypes |
| `src/main.c` | Program entry point, initialization |
| `src/algorithm/turk_sort.c` | Main sorting orchestration |
| `src/parsing/input_to_stack.c` | Input validation and stack initialization |
| `bonus/checker/checker_main.c` | Checker program entry point |

## Author

**danicort** - 42 school student

## Notes

- All integers must be unique
- Stack B starts empty
- The program must output operations one per line to stdout
- Memory is properly freed on exit and error
- The checker program validates operation sequences without outputting operation names

---

*Last updated: January 11, 2026*

