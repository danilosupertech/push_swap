# Contributing to Push Swap

First off, thank you for considering contributing to Push Swap! 🎉

## 📋 Table of Contents

- [Code of Conduct](#code-of-conduct)
- [How Can I Contribute?](#how-can-i-contribute)
- [Development Guidelines](#development-guidelines)
- [Coding Standards](#coding-standards)
- [Commit Messages](#commit-messages)

## 🤝 Code of Conduct

This project adheres to a code of conduct. By participating, you are expected to uphold this code:

- Be respectful and inclusive
- Welcome newcomers and help them learn
- Focus on what is best for the community
- Show empathy towards other community members

## 🛠️ How Can I Contribute?

### Reporting Bugs

Before creating bug reports, please check existing issues to avoid duplicates. When creating a bug report, include:

- **Clear title and description**
- **Steps to reproduce** the behavior
- **Expected behavior**
- **Actual behavior**
- **Environment details** (OS, compiler version, etc.)
- **Code samples** if applicable

### Suggesting Enhancements

Enhancement suggestions are tracked as GitHub issues. When creating an enhancement suggestion, include:

- **Clear title and description**
- **Use case** explaining why this enhancement would be useful
- **Possible implementation** if you have ideas

### Pull Requests

1. Fork the repository
2. Create a new branch (`git checkout -b feature/amazing-feature`)
3. Make your changes
4. Ensure code follows 42 Norminette standards
5. Test your changes thoroughly
6. Commit your changes (`git commit -m 'Add amazing feature'`)
7. Push to the branch (`git push origin feature/amazing-feature`)
8. Open a Pull Request

## 💻 Development Guidelines

### Setting Up Development Environment

```bash
# Clone your fork
git clone https://github.com/YOUR_USERNAME/push_swap.git
cd push_swap

# Build the project
make

# Run tests
./push_swap 3 2 1
```

### Testing Your Changes

Before submitting a pull request:

1. **Build without warnings**: `make` should complete without errors
2. **Test basic functionality**: Try various input sizes
3. **Check for memory leaks**: Use `valgrind --leak-check=full ./push_swap [args]`
4. **Verify Norminette compliance**: Run `norminette .`

### Performance Testing

```bash
# Test with different input sizes
./push_swap 3 2 1 | wc -l        # Should be ≤ 3
./push_swap 5 4 3 2 1 | wc -l    # Should be ≤ 12

# Test with 100 random numbers
ARG=$(shuf -i 1-1000 -n 100 | tr '\n' ' ')
./push_swap $ARG | wc -l         # Should be < 700
```

## 📏 Coding Standards

This project follows **42 Norminette** standards:

### File Structure
- Every file must have a 42 header comment
- Functions should be declared in header files
- Implementation in corresponding .c files

### Naming Conventions
- Functions: `lowercase_with_underscores`
- Variables: `lowercase_with_underscores`
- Structs: `typedef struct s_name { ... } t_name;`
- Constants: `UPPERCASE_WITH_UNDERSCORES`

### Code Style
- **Indentation**: Use tabs (not spaces)
- **Line length**: Maximum 80 characters per line
- **Function length**: Maximum 25 lines (when practical)
- **Parameters**: Maximum 4 parameters per function
- **No global variables**

### Documentation
- Add comments for complex algorithms
- Document non-obvious function behavior
- Keep comments concise and relevant

## 📝 Commit Messages

Write clear, descriptive commit messages:

### Format
```
type: Brief description (max 50 chars)

Detailed explanation if necessary (wrap at 72 chars)
```

### Types
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation changes
- `style`: Code style changes (formatting, norminette)
- `refactor`: Code refactoring
- `test`: Adding or updating tests
- `chore`: Maintenance tasks

### Examples

Good commit messages:
```
feat: Add support for negative numbers in parser
fix: Memory leak in stack_free function
docs: Update README with performance benchmarks
```

Bad commit messages:
```
fix stuff
updated files
WIP
```

## 🧪 Testing Checklist

Before submitting your PR, verify:

- [ ] Code compiles without warnings (`make`)
- [ ] Code follows Norminette standards (`norminette .`)
- [ ] No memory leaks (`valgrind --leak-check=full`)
- [ ] Basic functionality works (test with 3, 5, 100 numbers)
- [ ] Error handling works correctly
- [ ] Documentation is updated if needed
- [ ] Commit messages are clear and descriptive

## 📞 Questions?

If you have questions or need help:

1. Check existing issues and discussions
2. Open a new issue with the `question` label
3. Reach out to the maintainers

## 🙏 Thank You!

Your contributions make this project better for everyone. We appreciate your time and effort! 🌟

---

*Remember: Every expert was once a beginner. Don't hesitate to contribute!*
