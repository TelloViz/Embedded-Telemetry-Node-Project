// serial_io.h
#pragma once
#include <stddef.h>
#include <stdbool.h>

namespace hal::serial
{
    class ISerialIo
    {
    public:
        virtual ~ISerialIo() = default;
        virtual bool serial_readline(char *out, size_t out_cap) = 0;
        virtual void hal_serial_print(const char *str) = 0;
    };

    // Reads a single line from Serial into out (null-terminated).
    // Returns true only when a full line is available.
    // Non-blocking: returns false if no full line has arrived yet.
    class HalSerial : public ISerialIo
    {
    public:
        bool serial_readline(char *out, size_t out_cap) override;
        void hal_serial_print(const char *str) override;
    };
} // namespace hal::serial