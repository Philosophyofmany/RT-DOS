void kernel_main(void) {
    const char *message = "Hello from the Kernel!\n";

    // Simple loop to print each character
    char *vga = (char *)0xB8000;
    int i = 0;
    while (message[i] != 0) {
        vga[i * 2] = message[i];    // Character
        vga[i * 2 + 1] = 0x0F;     // Color (light gray on black)
        i++;
    }

    while (1);  // Infinite loop to prevent the kernel from exiting
}
