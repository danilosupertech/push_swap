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
├── libft/                  # Minimal libc reimplementation
│   ├── Makefile
│   ├── libft.h             # Public header (includes ft_split)
│   └── ft_*.c              # String, memory, and utility functions (incl. ft_split)
└── tests/                  # Test scripts (not submitted)
    ├── test_all.sh         # Functionality tests
    ├── test_memory.sh      # Memory leak detection
    └── test_performance.sh # Performance benchmarks
```

## Algorithm Details

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
- **100 numbers**: 500-600 operations
- **500 numbers**: 4900-5200 operations

## Testing

### Functionality test
```bash
chmod +x tests/test_all.sh
./tests/test_all.sh
```

### Performance test
```bash
chmod +x tests/test_performance.sh
./tests/test_performance.sh
```

### Memory test (requires valgrind)
```bash
chmod +x tests/test_memory.sh
./tests/test_memory.sh
```

**Note:** Test scripts are in the `tests/` folder and are not submitted to the 42 server. They are provided for local development and validation.

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

