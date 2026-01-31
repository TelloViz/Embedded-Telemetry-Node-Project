// serial_io.h
#pragma once
#include <stddef.h>
#include <stdbool.h>

// Reads a single line from Serial into out (null-terminated).
// Returns true only when a full line is available.
// Non-blocking: returns false if no full line has arrived yet.
bool serial_readline(char *out, size_t out_cap);