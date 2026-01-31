// serial_io.cpp
#include "serial_io.h"

#include <Arduino.h>
#include <string.h>

// Internal line accumulator
// This avoids blocking while waiting for '\n'.
static char s_line[128];
static size_t s_len = 0;

bool serial_readline(char *out, size_t out_cap)
{
    if (out == NULL || out_cap == 0)
        return false;

    while (Serial.available() > 0)
    {
        int ch = Serial.read();
        if (ch < 0)
            break; // No more data

        char c = (char)ch;

        // Ignore carriage return so both \n and \r\n line endings work
        if (c == '\r')
            continue;

        if (c == '\n')
        {
            // Complete line raedy.
            s_line[s_len] = '\0'; // Null-terminate

            // Copy into caller buffer safely.
            strncpy(out, s_line, out_cap - 1);
            out[out_cap - 1] = '\0'; // Ensure null-termination

            // Reset accumulator for next line.
            s_len = 0;
            return true;
        }

        // Append if space remains, else drop the line (simple overflow policy).
        if (s_len < sizeof(s_line) - 1)
        {
            s_line[s_len++] = c;
        }
        else
        {
            // Overflow: reset and return false (line was too long).
            s_len = 0;
            return false;
        }
    }

    return false;
}