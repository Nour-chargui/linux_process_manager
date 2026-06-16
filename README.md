# Linux Process Manager

A lightweight, modular process manager for Linux systems, built in C using the `/proc` filesystem and Linux system calls.

## Features
- **Process Enumeration**: Reads `/proc` to list all running processes.
- **Detailed Stats**: Displays PID, process name, state, and memory usage (RSS).
- **Search functionality**: Find processes by name or PID.
- **Process Termination**: Safely kill processes (sends `SIGKILL`) with user confirmation.
- **Sorting**: Sort processes by CPU time usage.
- **Modular Design**: Clean separation between process logic, UI, and main entry point.

## Requirements
- Linux operating system.
- `gcc` compiler.
- `make` utility.

## Setup & Compilation

1. **Navigate** to the project directory:
   ```bash
   cd linux_process_manager
   ```
2. **Build** the project:
   ```bash
   make
   ```
3. **Run** the manager:
   ```bash
   ./proc_manager
   ```

## Design Decisions
- **The `/proc` Filesystem**: Leveraged the Linux virtual filesystem `/proc` as the source of truth for process information, avoiding complex kernel-level programming.
- **Modular Architecture**: 
    - `process.c`: Handles all low-level `/proc` parsing and system calls.
    - `ui.c`: Responsible for terminal output formatting.
    - `main.c`: Manages the application lifecycle and user input loop.
- **Dynamic Memory**: Uses dynamic allocation to handle a variable number of processes efficiently.
- **Safety**: Implemented a confirmation step before killing processes to prevent accidental system instability.

## Project Structure
```
.
├── include
│   └── process.h    # Header with data structures and prototypes
├── src
│   ├── main.c       # Main entry point and menu loop
│   ├── process.c    # /proc parsing and process logic
│   └── ui.c         # Display and UI formatting
├── Makefile         # Build configuration
└── README.md        # Documentation
```
