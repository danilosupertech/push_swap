<div align="center">

# 🔄 Push Swap

[![42 Project](https://img.shields.io/badge/42-Project-00babc?style=flat-square&logo=42)](https://www.42.fr/)
[![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=flat-square)](https://github.com/42School/norminette)
[![License](https://img.shields.io/badge/License-MIT-yellow?style=flat-square)](LICENSE)

*An efficient sorting algorithm implementation using two stacks*

**By [danicort](https://github.com/danilosupertech) - 42 School**

[Features](#-features) • [Installation](#-installation) • [Usage](#-usage) • [Algorithm](#-algorithm) • [Testing](#-testing)

---

</div>

## 📖 Overview

**push_swap** is a sorting algorithm project that sorts integers using two stacks and a limited set of operations. The goal is to produce the shortest sequence of operations to sort stack A in ascending order while keeping stack B empty.

This implementation uses the **Turk algorithm**, a cost-based greedy strategy that picks the cheapest move at each step by computing rotation and push costs.

## ✨ Features

- 🚀 **Efficient Turk Algorithm** - Optimized cost-based sorting
- 📊 **Performance Optimized** - Meets strict 42 evaluation requirements
- 🧩 **Modular Design** - Clean, organized code structure
- 🔍 **Comprehensive Error Handling** - Validates all inputs
- 💾 **Memory Safe** - Zero memory leaks (Valgrind tested)
- 📝 **Norminette Compliant** - Follows 42 coding standards

## 🔧 Requirements

- **C compiler**: `gcc` or `clang`
- **Make**: Build automation tool
- **Norminette** (optional): For 42 code style validation

## 📥 Installation

### Clone the Repository

```bash
git clone https://github.com/danilosupertech/push_swap.git
cd push_swap
```

## 🏗️ Building

### Compile the Project

```bash
make
```

### Clean Build Files

```bash
make clean      # Remove object files
make fclean     # Remove object files and binaries
make re         # Full rebuild
```

## 🚀 Usage

### Basic Examples

```bash
./push_swap 3 2 1
./push_swap "3 2 1"
./push_swap 42 -5 100 0
```

### Quick Start

```bash
# Sort 5 random numbers
./push_swap 5 2 8 1 9

# Count operations
./push_swap 5 2 8 1 9 | wc -l

# Test with 100 numbers
ARG=$(shuf -i 1-1000 -n 100 | tr '\n' ' '); ./push_swap $ARG | wc -l
```

## 📋 Allowed Operations

| Operation | Description | Effect |
|-----------|-------------|--------|
| `sa` | Swap A | Swap first 2 elements of stack A |
| `sb` | Swap B | Swap first 2 elements of stack B |
| `ss` | Swap Both | Swap both stacks simultaneously |
| `pa` | Push to A | Push top element from B to A |
| `pb` | Push to B | Push top element from A to B |
| `ra` | Rotate A | Rotate stack A (move first to last) |
| `rb` | Rotate B | Rotate stack B (move first to last) |
| `rr` | Rotate Both | Rotate both stacks |
| `rra` | Reverse Rotate A | Reverse rotate A (move last to first) |
| `rrb` | Reverse Rotate B | Reverse rotate B (move last to first) |
| `rrr` | Reverse Rotate Both | Reverse rotate both stacks |

## ⚠️ Error Handling

The program outputs `Error\n` to stderr and exits with status 1 if:

- ❌ Input contains non-integer tokens
- ❌ Input contains duplicate values
- ❌ Integer values overflow `int` range
- ❌ Memory allocation fails

✅ Otherwise exits with status 0 on success.

## 📁 Project Structure

```
push_swap/
├── 📄 Makefile                 # Build configuration
├── 📖 README.md               # Project documentation
├── 📂 includes/
│   └── push_swap.h            # Main header (data structures, prototypes)
├── 📂 src/
│   ├── main.c                 # Entry point and orchestration
│   ├── 📂 commands/           # Basic stack operations
│   │   ├── swap_ops.c         # sa, sb, ss
│   │   ├── push_ops.c         # pa, pb
│   │   ├── rotate_ops.c       # ra, rb, rr
│   │   └── rev_rotate_ops.c   # rra, rrb, rrr
│   ├── 📂 algorithm/          # Turk sorting algorithm
│   │   ├── turk_sort.c        # Main orchestration
│   │   ├── small_cases.c      # Sort 2-3 elements
│   │   ├── final_rotation.c   # Position minimum on top
│   │   ├── init_nodes.c       # Initialize node metadata
│   │   ├── find_targets.c     # Find target positions
│   │   ├── calc_costs.c       # Calculate movement costs
│   │   ├── execute_moves.c    # Execute optimal moves
│   │   └── rotation_moves.c   # Combined rotations helpers
│   ├── 📂 parsing/            # Input validation and parsing
│   │   ├── input_to_stack.c   # Main parsing orchestration
│   │   ├── parse_validate.c   # Integer validation
│   │   └── parse_split_free.c # Free helper for split arrays
│   └── 📂 stack/              # Stack utilities
│       ├── stack_nav.c        # Navigation (length, find last)
│       ├── stack_order.c      # Order analysis (sorted, min, max)
│       └── stack_ops.c        # Memory management (append, free)
└── 📂 libft/                  # Custom C library
    └── ...                    # Standard library functions
```

## 🧠 Algorithm Details

### 🔹 Commands Module

The **commands/** folder implements the 11 basic stack operations mandated by the subject:

- **swap_ops.c**: Implements `sa` (swap first 2 of A), `sb` (swap first 2 of B), and `ss` (swap both)
- **push_ops.c**: Implements `pa` (push top of B to A) and `pb` (push top of A to B)
- **rotate_ops.c**: Implements `ra` (rotate A up), `rb` (rotate B up), and `rr` (rotate both)
- **rev_rotate_ops.c**: Implements `rra` (rotate A down), `rrb` (rotate B down), and `rrr` (rotate both down)

All operations run in **O(1) time** by only manipulating top/bottom node pointers. Each operation prints its name to stdout when executed.

### 🔹 Parsing Module

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

### 🔹 Stack Module

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

### 🔹 Turk Algorithm

The Turk algorithm uses a cost-based greedy approach:

1. **Initialization** 🎯 Calculate positions and target positions for each element
2. **Cost Calculation** 💰 For each element in stack A, calculate the cost to:
   - Move it to the top of A
   - Find its target position in B
   - Move it to that target
   - Position the receiver element optimally
3. **Selection** 🎲 Choose the cheapest move
4. **Execution** ⚡ Perform optimal combined rotations
5. **Completion** 🔄 Repeat until A is sorted and B is empty
6. **Final Rotation** 🔝 Rotate A so the smallest element is on top

### 📊 Performance

Expected results for typical inputs:

| Input Size | Operations | Target | Status |
|------------|-----------|--------|--------|
| 3 numbers | ≤ 3 | 3 | ✅ |
| 5 numbers | ≤ 12 | 12 | ✅ |
| 100 numbers | < 700 | 500-600 | ✅ |
| 500 numbers | < 5500 | 4900-5200 | ✅ |

These limits align with 42 evaluation requirements for maximum score.

## 🧪 Testing Examples

### ✅ Basic Functionality

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

### 📊 Count Operations

```bash
# Small set (3 numbers) - should use ≤ 3 operations
./push_swap 2 1 3 | wc -l

# Medium set (5 numbers) - should use ≤ 12 operations
./push_swap 5 4 3 2 1 | wc -l

# Large set (100 numbers) - should use < 700 operations
ARG=$(shuf -i 1-1000 -n 100 | tr '\n' ' '); ./push_swap $ARG | wc -l
```

### ✔️ Validate with Checker

```bash
# If you have checker program
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG
# Expected output: OK

# Test with invalid input
./push_swap 1 2 3 2
# Expected output: Error
```

### 🔍 Memory Leak Detection

```bash
# Install valgrind (Ubuntu/Debian)
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
```

## 💻 Code Style

This project follows **42 Norminette** standards:

- ✅ 42 header comment in every file
- ✅ Tab indentation
- ✅ Functions ≤ 25 lines (when practical)
- ✅ No global variables
- ✅ Clear function documentation

To validate locally:
```bash
norminette .
```

## 🗂️ Data Structures

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

## 📚 Key Files Reference

| File | Purpose |
|------|---------|
| `includes/push_swap.h` | Data structures and function prototypes |
| `src/main.c` | Program entry point, initialization |
| `src/algorithm/turk_sort.c` | Main sorting orchestration |
| `src/parsing/input_to_stack.c` | Input validation and stack initialization |

## 🤝 Contributing

Contributions are welcome! Please feel free to:

1. 🐛 Report bugs
2. 💡 Suggest new features
3. 🔧 Submit pull requests
4. 📖 Improve documentation

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👤 Author

**Danilo Cortez (danicort)**
- 🏫 42 School Student
- 🐙 GitHub: [@danilosupertech](https://github.com/danilosupertech)

## 📌 Notes

- ✅ All integers must be unique
- ✅ Stack B starts empty
- ✅ The program outputs operations one per line to stdout
- ✅ Memory is properly freed on exit and error
- ✅ Zero memory leaks (Valgrind tested)

## 🙏 Acknowledgments

- 42 School for the project subject
- The Turk algorithm community for optimization strategies
- Fellow 42 students for testing and feedback

---

<div align="center">

**⭐ If you found this project helpful, consider giving it a star!**

*Last updated: January 2026*

</div>
