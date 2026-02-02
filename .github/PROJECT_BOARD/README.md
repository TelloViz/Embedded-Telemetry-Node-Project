# Project Board Issues - TDD Workflow

This directory contains structured issue templates for implementing a Test-Driven Development (TDD) workflow for the Embedded Telemetry Node project.

## 📋 Overview

These templates follow a strict TDD approach where:
1. **Tests are written first** - every story starts with defining test cases
2. **Native tests run first** - tests run on Windows/Linux without hardware
3. **Implementation follows tests** - code is written to make tests pass
4. **Device tests validate integration** - hardware tests validate the complete stack
5. **CI/CD ensures quality** - automated testing on every commit

## 📁 Directory Structure

```
PROJECT_BOARD/
├── 00-EPIC-TDD-ROADMAP.md          # Overall project epic
├── PHASE-1-CRC16/                  # CRC16 Implementation (5 stories)
├── PHASE-2-PACKET-SERIALIZATION/   # Packet Serialization (5 stories)
├── PHASE-3-COMMAND-PARSER/         # Command Parser (5 stories)
├── PHASE-4-DEVICE-INTEGRATION/     # Device Integration (4 stories)
├── PHASE-5-CICD/                   # CI/CD Automation (4 stories)
├── LABELS.md                       # GitHub label definitions
├── KANBAN_STRUCTURE.md             # Kanban board setup guide
└── README.md                       # This file
```

## 🚀 Quick Start

### 1. Set Up GitHub Project Board

Follow instructions in `KANBAN_STRUCTURE.md` to create a GitHub Project with kanban columns.

### 2. Create GitHub Labels

Use `LABELS.md` to create all necessary labels in your repository:
- Phase labels (phase-1 through phase-5)
- Category labels (test-first, protocol, etc.)
- Priority labels (priority-high, priority-medium, priority-low)
- Technology labels (crc16, serialization, etc.)

### 3. Create Issues

For each `.md` file in the phase directories:

1. Create a new GitHub issue
2. Use the markdown content as the issue description
3. Apply appropriate labels from LABELS.md
4. Assign to the milestone for that phase
5. Add to your project board
6. Set dependencies using task lists

**Example using GitHub CLI:**
```bash
gh issue create \
  --title "[Phase 1] Implement CRC16 Empty Buffer Test" \
  --body-file .github/PROJECT_BOARD/PHASE-1-CRC16/01-crc16-empty-buffer-test.md \
  --label "phase-1,test-first,protocol,crc16" \
  --milestone "Phase 1 - CRC16 Implementation" \
  --project "Embedded Telemetry TDD Roadmap"
```

### 4. Follow the TDD Workflow

For each story:

1. **Write Tests First** (Acceptance Criteria)
   ```bash
   # Add tests to test/test_protocol.cpp
   platformio test -e native -f test_name
   # Tests should fail initially (no implementation yet)
   ```

2. **Implement to Pass Tests**
   ```bash
   # Implement in firmware/lib/protocol/ or firmware/src/
   platformio test -e native
   # Iterate until all tests pass
   ```

3. **Verify Device Build**
   ```bash
   platformio run -e rpipico2w
   # Ensure code compiles for target hardware
   ```

4. **Commit and Push**
   ```bash
   git add .
   git commit -m "[Phase 1] Implement CRC16 empty buffer handling"
   git push
   ```

5. **Create Pull Request**
   - Reference the issue number in PR description
   - Wait for CI/CD tests to pass
   - Get code review
   - Merge when approved

## 📊 Roadmap Phases

### Phase 1: CRC16 Implementation (12-20 hours)
- Foundation for packet integrity checking
- 5 stories covering empty buffers, known values, edge cases, incremental computation, and packet integration
- **Start here** - no dependencies

### Phase 2: Packet Serialization (16-24 hours)
- Binary packet format with headers, payload, and CRC
- 5 stories covering structure definition, serialization, deserialization, buffer management, and endianness
- **Depends on:** Phase 1 complete

### Phase 3: Command Parser (16-24 hours)
- Parse and handle remote commands
- 5 stories covering command structure, parsing, response generation, handler framework, and built-in handlers
- **Depends on:** Phase 2 complete

### Phase 4: Device Integration Tests (12-16 hours)
- Test protocol stack on actual Raspberry Pi Pico 2W hardware
- 4 stories covering serial transmission/reception, performance benchmarks, and error recovery
- **Depends on:** Phase 3 complete
- **Requires:** Raspberry Pi Pico 2W hardware

### Phase 5: CI/CD Automation (12-16 hours)
- Automated testing and deployment pipeline
- 4 stories covering unit test automation, build automation, code coverage, and documentation generation
- **Depends on:** Phases 1-3 complete (can start in parallel with Phase 4)

## 🎯 Success Criteria

Project is complete when:
- [ ] All 23 stories implemented and tested
- [ ] All native unit tests passing (`platformio test -e native`)
- [ ] Device integration tests documented and passing
- [ ] CI/CD pipeline running on every PR
- [ ] Code coverage ≥80% for protocol layer
- [ ] Firmware builds successfully for rpipico2w
- [ ] Documentation updated and published

## 🛠 Development Workflow

Each story follows this pattern:

1. **Acceptance Criteria** - Specific tests that must pass
2. **Implementation Tasks** - Step-by-step checklist
3. **Technical Notes** - Design decisions and specifications
4. **Definition of Done** - Completion checklist
5. **Related Issues** - Dependencies and blockers
6. **References** - Relevant files and documentation

## 📖 Additional Resources

- [TESTING.md](../../docs/TESTING.md) - Complete testing strategy
- [TESTING_QUICK_START.md](../../docs/TESTING_QUICK_START.md) - Quick reference for developers
- [design.md](../../docs/design.md) - System architecture and design
- [README.md](../../README.md) - Project overview

## 🤝 Contributing

When implementing stories:
1. Follow TDD approach strictly - tests before implementation
2. Ensure all tests pass before moving to next story
3. Update test copies if modifying app logic (`test/app_impl.cpp` from `firmware/src/app.cpp`)
4. Document any deviations or issues in the story's GitHub issue
5. Update this README if you discover process improvements

## 📝 Notes

- **Estimation Format:** Hours are rough estimates for a single developer
- **Test-First is Critical:** Do not skip writing tests first
- **Native Testing:** Run tests on native platform before hardware testing
- **Incremental Progress:** Complete stories in order within each phase
- **Dependencies:** Later phases depend on earlier phases being complete

## 🔗 Links

- **Repository:** https://github.com/TelloViz/Embedded-Telemetry-Node-Project
- **Issues:** https://github.com/TelloViz/Embedded-Telemetry-Node-Project/issues
- **Projects:** https://github.com/TelloViz/Embedded-Telemetry-Node-Project/projects

---

**Total Estimated Effort:** 68-100 hours  
**Target Completion:** Q1 2026  
**Last Updated:** February 2026
