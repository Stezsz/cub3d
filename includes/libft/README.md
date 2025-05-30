
# 📚 Libft

**Libft** is a custom C library designed for use in academic projects at 42. This library includes a variety of useful functions, such as reimplementations of `libc` functions, additional utilities, and integrated versions of **get_next_line** and **ft_printf**.

This repository is fully integrated and compiles everything seamlessly. By including `libft.h` in your project, you gain access to all the library's features.

## Usage

To get started, clone this repository and navigate to its directory:

```bash
git clone https://github.com/leite-tiago/libft.git
cd libft
```

### Makefile Options

The `Makefile` provides several options for managing the project:

- **`make` or `make all`**: Compiles the library and generates the `libft.a` file.
- **`make clean`**: Removes object files (`*.o`) created during the compilation process.
- **`make fclean`**: Performs `clean` and deletes the compiled library (`libft.a`).
- **`make re`**: Runs `fclean` followed by `all`, recompiling the entire library from scratch.
- **`make bonus`**: Compiles the library with bonus functions if available.

### Including the Library

After running `make`, a `libft.a` file is generated at the root of the repository. Link it to your project by including `libft.h` in your source files and linking `libft.a` during compilation. For example:

```c
#include "libft.h"

int main() {
    char *str = ft_strdup("Hello, Libft!");
    ft_putstr_fd(str, 1);
    free(str);
    return 0;
}
```

Compile the program with:

```bash
gcc -Wall -Wextra -Werror main.c -L. -lft
```

This links your program with the `libft.a` library.

### Notes

- The library integrates **get_next_line** and **ft_printf**. Including `libft.h` gives access to these features as well.
- Ensure you meet the [42 Norm](https://github.com/42School/norminette) requirements if this is for academic purposes.
