#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

void _exit(int status) {
    while (1) { }
}

int _write(int file, char *ptr, int len) {
    // Minimal write implementation; modify as needed
    return len;
}

int _sbrk(int incr) {
    // Minimal heap allocation; should be replaced with real memory management
    extern char _end; // Defined in the linker script
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0) {
        heap_end = &_end;
    }
    prev_heap_end = heap_end;
    heap_end += incr;

    return (int)prev_heap_end;
}

int _close(int file) {
    return -1;
}

int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file) {
    return 1;
}

int _lseek(int file, int ptr, int dir) {
    return 0;
}

int _read(int file, char *ptr, int len) {
    return 0;
}
