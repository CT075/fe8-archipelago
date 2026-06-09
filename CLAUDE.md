# fe8-archipelago

## Code Style
- Keep all event files ASCII. Do not use em-dashes (`—`) or other non-ASCII characters in comments; use `--` instead.

### C files
- Run clang-format before committing any C file. The repo has a `.clang-format` at the root.
  ```
  clang-format -i <file.c>
  ```
  The VS Code C/C++ extension binary works if `clang-format` is not on PATH:
  ```
  ~/.vscode/extensions/ms-vscode.cpptools-*/LLVM/bin/clang-format -i <file.c>
  ```

### Event file include structure
- Do not use `#include "../<anything>"` in event files. Traversing up with `../` is a smell.
