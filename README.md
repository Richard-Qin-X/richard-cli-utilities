# Richard CLI Utilities

## Overview

Richard CLI Utilities is a simple and modular command-line toolkit built with modern C++20. It provides a lightweight router (`rcli`) that can launch various sub-tools (such as `clock`) using absolute path resolution. The core library handles basic terminal and signal management, aiming for clarity and maintainability. This project is suitable for users who want to organize and extend their own command-line utilities in a clean way.

## Build

Requires CMake 3.20.3+ and a C++20 compiler (GCC 13+ / Clang 16+).

```Bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
```

### Options

|**Flag**|**Default**|**Description**|
|---|---|---|
|`ENABLE_CLANG_TIDY`|`ON`|Run full static analysis|
|`CMAKE_EXPORT_COMPILE_COMMANDS`|`ON`|Generate compile_commands.json for LSP/Tidy|

### Format & Lint

```Bash
cmake --build build --target format        # auto-format all sources via clang-format
cmake --build build --target format-check  # check format compliance (dry-run)
```

## Run

Executables are unified in `build/bin/`. You can invoke sub-tools through the router:

```Bash
./build/bin/rcli clock
```

Or execute them directly:

```Bash
./build/bin/rcli-clock
```

## Project Structure

- `src/core/`: Terminal raw mode, signal handlers, and shared utilities.
    
- `src/tools/`: Independent sub-command implementations.
    
- `include/`: Public API headers for the core library.
    
- `src/main.cc`: Router logic with absolute path resolution.
    

## License

This project is licensed under the [GNU General Public License v3.0 or later](https://www.gnu.org/licenses/gpl-3.0.html). See [LICENSE](https://www.google.com/search?q=LICENSE) for details.