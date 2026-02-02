# EPIC: Test-Driven Development Roadmap for Embedded Telemetry Project

**Type:** Epic  
**Status:** Open  
**Priority:** High  
**Labels:** `epic`, `test-first`, `roadmap`  

## Overview

This epic tracks the implementation of a complete test-driven development workflow for the Embedded Telemetry Node project running on Raspberry Pi Pico 2W. Following TDD principles, each feature begins with unit tests, runs on native platforms first, and only moves to device integration after protocol/app layers are solid.

## Project Structure

- **Language:** C++/C
- **Testing Framework:** Unity (native) + device integration tests
- **Workflow:** Test-Driven Development (tests first, then implementation)
- **Repository:** GitHub with dev/main branches
- **Platform:** Raspberry Pi Pico 2W (RP2350)

## Development Workflow Rules

1. ✅ Every feature starts with unit tests in `test/test_*.cpp`
2. ✅ Tests run on native (Windows/Linux) first - no hardware needed
3. ✅ After tests pass, implement in `firmware/src/` or `firmware/lib/`
4. ✅ Device tests come after protocol/app layer is solid
5. ✅ Update test copies (e.g., `test/app_impl.cpp` from `firmware/src/app.cpp`)

## Roadmap Phases

### Phase 1: CRC16 Implementation
**Goal:** Implement CRC16 checksum for packet integrity  
**Duration:** 12-20 hours  
**Stories:** 5

- Unit tests for CRC16 computation
- Implementation in protocol library
- Edge case handling
- Integration with packet structure

### Phase 2: Packet Serialization
**Goal:** Implement binary packet format with headers, payload, and CRC  
**Duration:** 16-24 hours  
**Stories:** 5

- Packet structure definition
- Serialization functions
- Deserialization functions
- Buffer management
- Endianness handling

### Phase 3: Command Parser
**Goal:** Parse incoming commands and generate responses  
**Duration:** 16-24 hours  
**Stories:** 5

- Command structure definition
- Parser implementation
- Response generation
- Error handling
- Command validation

### Phase 4: Device Integration Tests
**Goal:** Test protocol stack on actual hardware  
**Duration:** 12-16 hours  
**Stories:** 4

- Serial communication tests
- End-to-end packet flow
- Performance benchmarks
- Error recovery tests

### Phase 5: CI/CD Automation
**Goal:** Automated testing and deployment pipeline  
**Duration:** 12-16 hours  
**Stories:** 4

- GitHub Actions for unit tests
- Build automation for device code
- Code coverage reporting
- Automated documentation generation

## Success Criteria

- [ ] All phases completed with passing tests
- [ ] 80%+ unit test coverage for protocol layer
- [ ] Native tests run in < 5 seconds
- [ ] Device integration tests documented and reproducible
- [ ] CI/CD pipeline runs on every PR
- [ ] Documentation updated for each phase

## Dependencies

- PlatformIO toolchain configured
- Unity test framework integrated
- Raspberry Pi Pico 2W hardware available for Phase 4+

## Related Documentation

- [TESTING.md](../../docs/TESTING.md) - Testing strategy
- [TESTING_QUICK_START.md](../../docs/TESTING_QUICK_START.md) - Developer quick reference
- [design.md](../../docs/design.md) - System design

## Notes

This epic follows a strict TDD approach where:
- Tests are written before implementation
- Native tests validate logic without hardware
- Device tests validate hardware integration
- Each story includes specific acceptance criteria (test names)
- Implementation tasks are defined after test requirements

---

**Estimated Total Duration:** 68-100 hours  
**Target Completion:** Q1 2026
