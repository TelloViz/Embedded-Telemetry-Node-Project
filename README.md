# Embedded Telemetry Node

An embedded systems project implementing a telemetry collection node for the Raspberry Pi Pico 2W with hardware abstraction, dependency injection, and comprehensive testing.

## Project Overview

This project implements a telemetry collection node that:
- Collects and transmits telemetry data over serial/network interfaces
- Handles remote commands and configuration
- Maintains operational state and fault tracking
- Provides hardware abstraction through clean interfaces

---

## Architecture

### Design Philosophy
- **Hardware Abstraction Layer (HAL)**: All hardware dependencies (LED, serial, timing) are abstracted behind interfaces
- **Dependency Injection**: Core application logic accepts all dependencies, enabling comprehensive testing
- **Platform Agnostic**: Application layer (`app.cpp`) contains zero platform-specific code
- **Testable by Default**: Mock implemenations enable unit testing through Unity Test without hardware

### Core Components
```sh
firmware/
├── src/
│   ├── app.cpp/app.h          # Core application logic (state machine, telemetry)
│   ├── main.cpp               # Arduino entry point & hardware initialization
│   └── hal/
│       ├── led/               # LED control abstraction
│       ├── time/              # Time/millis() abstraction
│       ├── serial/            # Serial I/O abstraction
│       └── logging/           # Logging interface
└── lib/
    └── protocol/              # Packet formatting, CRC, parsing

test/
├── test_app.cpp               # Unit tests for application logic
├── test_protocol.cpp          # Unit tests for protocol layer
└── app_impl.cpp               # Copy of app.cpp for test builds
```

---

## Getting Started

### Prerequisites
- **PlatformIO IDE** (VS Code extension recommended)
- **Python 3.x** (PlatformIO requirement)
- **Git** (for version control)
- **MinGW** or similar (for native test compilation on Windows)

### Build & Test

**Run native unit tests (no hardware required):**
```bash
platformio test -e native
```

**Build for Raspberry Pi Pico 2W:**
```bash
platform run -e rpipico2w
```

**Upload to device:**
```bash
platformio run -e rpipico2w --target upload
```

**Monitor serial output:**
```bash
platformio device monitor --port COM3 --baud 115200
```

For more detailed commands and workflows, see [TESTING_QUICK_START.md](TESTING_QUICK_START.md)

---

## Testing Strategy

This project implments **native unit testing** with a roadmap for integration and device-level testing.

### Current: Unit Tests (MVP)
- **4 passing tests** covering initialization, LED control, heartbeat, and command handling
- **Dependency injection** with comprehensive mocks
- **Zero hardware dependency** -- tests run on Windows/Linux/Mac
- **Framework**: Unity Test

### Future Roadmap
See [docs/TESTING.md](docs/Testing.md) for the complete testing strategy including:
- Phase 2: Enhanced unit test coverage (80%+ line coverage)
- Phase 3: Integration tests with concrete HA implementations
- Phase 4: Device integration tests on hardware
- Phase 5: CI/CD automation with GitHub Actions

---

## Design Documentation

- ** [docs/TESTING.md](docs/TESTING.md)** - Testing, strategy, roadmap, and architectue decisions
- **[TESTING_QUICK_START.md](docs/TESTING_QUICK_START.md)** - Developer quick reference for running tests
- **[docs/design.md](docs/design.md)** - High-level system design
- **[docs/demo.md](docs/demo.md)** - Demo usage and examples

## Key Features

-> **Architecture**
- Dependency injection pattern for testability
- Hardware abstraction layer (HAL) interfaces
- Zero platform-specific code in application layer
- Clear separation of concerns

-> **Testing**
- Native unit tests with dependency injection mocks
- Tests run on Windows/Linux/Mac (no hardware required)
- Measurable test coverage
- Roadmap for integration and device testing

-> **Embedded Design**
- Non-blocking event loop
- State machine pattern for application logic
- Resource-efficient (designed for 512KB RAM device)
- Fault tracking and error handling

---

## Development Workflow

1. **Make changes** to `firmware/src/app.cpp` or HAL implementations
2. **Update test copy** if app logic changes:
   ```bash
   copy firmware\src\app.cpp test\app_impl.cpp  # Windows
   cp firmware/src/app.cpp test/app_impl.cpp    # Linux/Mac
   ```
3. **Run tests** to validate: `platformio test -e native`
4. **Build device code** when ready: `platformio run -e rpipico2w`

---

## Technical Specifications

**Hardware Target:**
- Raspberry Pi Pico 2W
- RP2350 ARM Cortex-M33 @ 150MHz
- 512KB RAM, 4MB Flash
- Arduino framework compatibility

**Software Stack:**
- C++ (C++17)
- Arduino framework (Earle Philhower core)
- Unity test framework
- CMake for test builds

**Supported Boards:**
- `rpipico2w` - Pico 2W (production)
- `native` - Windows/Linux desktop (testing)

---

## Repository Structure

```
.
├── firmware/              # Device firmware
│   ├── src/              # Application source code
│   ├── lib/              # Libraries (protocol, utilities)
│   └── include/          # Header files
├── test/                 # Unit tests
├── docs/                 # Documentation
├── host/                 # Host-side utilities (CLI, tools)
├── platformio.ini        # PlatformIO configuration
├── README.md             # This file
└── .gitignore           # Git ignore rules
```

---

## Learning Resources

This project demonstrates several embedded systems patterns:

1. **Dependency Injection** - Enables testing without hardware
2. **Hardware Abstraction Layer** - Decouples business logic from hardware details
3. **State Machine Pattern** - Manages application state transitions
4. **Mock Objects** - Enables comprehensive unit testing without hardware
5. **Non-Blocking Design** - Responsive event-driven architecture

---

## Future Enhancements

Planned improvements (see [docs/TESTING.md](docs/TESTING.md) for details):
- [ ] Expand unit test coverage to 80%+
- [ ] Integration tests with concrete HAL implementations
- [ ] Device integration tests on Pico 2W hardware
- [ ] CI/CD pipeline with GitHub Actions
- [ ] Protocol library implementation (packet formatting, CRC)
- [ ] Migration to GoogleTest framework (optional)

---

## Contributing

When adding features or bug fixes:
1. Write tests first (TDD approach preferred)
2. Ensure `platformio test -e native` passes
3. Verify `platformio run -e rpipico2w` builds successfully
4. Update documentation if behavior changes

---

## License

See [LICENSE](LICENSE) file for details.

---

## Contact & Questions

For questions about the architecture, testing strategy, or implementation details, refer to:
- [docs/TESTING.md](docs/TESTING.md) - Testing strategy and decisions
- [docs/design.md](docs/design.md) - System design documentation
- Inline code comments and docstrings in source files

---

**Last Updated**: February 2026  
**Status**: MVP - Unit testing and core architecture complete

