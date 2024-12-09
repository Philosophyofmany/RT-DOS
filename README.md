# RT-DOS

## Prerequisites

To build, load, and run this experimental kernel, the following tools and setup are required:

1. **x86_64-elf Toolchain**:  
   This is essential to cross-compile the kernel. Ensure the toolchain is correctly installed and configured in your development environment.

2. **QEMU Emulator**:  
   Used to emulate the x86-64 architecture for testing the kernel without requiring physical hardware.

3. **Make Utility**:  
   Run `make` to compile the kernel and `make run` to launch it in QEMU.

---

## About the Kernel

This kernel is an **experimental 64-bit kernel** designed to run on x86-64 systems. It is in active development and will be updated regularly with new features. Current work is focused on the following components:

- **Keyboard Driver**: Enables input handling and interaction with the system.
- **Screen Driver**: Manages text output and cursor movement on the screen.
- **Shell**: A basic command-line interface allowing users to interact with the kernel through simple commands.

### Planned Features

Future updates aim to expand the kernel's functionality, introducing more advanced features to enhance its usability and explore additional OS concepts. Stay tuned for new developments!  
