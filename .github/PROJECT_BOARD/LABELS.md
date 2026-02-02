# GitHub Labels for TDD Workflow

This document defines the labels to be created in the GitHub repository for organizing issues and tracking progress.

## Phase Labels

Use these labels to indicate which roadmap phase an issue belongs to:

- **`phase-1`** - Phase 1: CRC16 Implementation
- **`phase-2`** - Phase 2: Packet Serialization
- **`phase-3`** - Phase 3: Command Parser
- **`phase-4`** - Phase 4: Device Integration Tests
- **`phase-5`** - Phase 5: CI/CD Automation

## Category Labels

Use these labels to categorize the type of work:

- **`test-first`** - Issues following TDD approach (write tests first)
- **`protocol`** - Protocol layer implementation
- **`app-layer`** - Application layer implementation
- **`device-test`** - Device integration testing on hardware
- **`ci-cd`** - CI/CD pipeline and automation
- **`automation`** - General automation tasks
- **`documentation`** - Documentation updates

## Type Labels

Use these labels to indicate the issue type:

- **`epic`** - Large, multi-phase initiative
- **`story`** - User story (feature increment)
- **`task`** - Individual task or subtask
- **`bug`** - Bug fix
- **`enhancement`** - Enhancement to existing feature

## Priority Labels

Use these labels to indicate priority:

- **`priority-high`** - High priority (must have)
- **`priority-medium`** - Medium priority (should have)
- **`priority-low`** - Low priority (nice to have)

## Technology Labels

Use these labels to indicate technology area:

- **`crc16`** - CRC16 checksum implementation
- **`serialization`** - Packet serialization/deserialization
- **`command-parser`** - Command parsing and handling
- **`serial`** - Serial communication
- **`integration`** - Integration testing
- **`performance`** - Performance and benchmarking
- **`reliability`** - Error handling and recovery
- **`buffer-management`** - Buffer and memory management
- **`portability`** - Cross-platform portability
- **`optimization`** - Performance optimization
- **`github-actions`** - GitHub Actions workflows
- **`code-coverage`** - Code coverage tracking

## Status Labels (Optional)

Use these if you want to track status in addition to GitHub's built-in states:

- **`status-blocked`** - Blocked by another issue or dependency
- **`status-in-progress`** - Currently being worked on
- **`status-needs-review`** - Ready for code review
- **`status-needs-testing`** - Needs manual testing

## Creating Labels in GitHub

You can create these labels manually in GitHub or use the GitHub CLI:

```bash
# Example: Create a label with the gh CLI
gh label create "phase-1" --description "Phase 1: CRC16 Implementation" --color "0052CC"
gh label create "test-first" --description "TDD approach - write tests first" --color "7057ff"
gh label create "protocol" --description "Protocol layer implementation" --color "bfd4f2"
```

## Recommended Label Colors

- **Phase labels**: Blue shades (e.g., #0052CC, #0065FF)
- **Category labels**: Purple shades (e.g., #7057FF, #5319E7)
- **Priority labels**: Red/Orange/Yellow (High=#D73A4A, Medium=#FBCA04, Low=#0E8A16)
- **Type labels**: Gray shades (e.g., #D4C5F9, #C5DEF5)
- **Technology labels**: Green/Teal shades (e.g., #BFD4F2, #C2E0C6)
