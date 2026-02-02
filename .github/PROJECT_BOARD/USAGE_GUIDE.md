# How to Use the Project Board Templates

This guide explains how to use the issue templates and scripts in `.github/PROJECT_BOARD/` to set up your TDD workflow and project management.

## Overview

The `.github/PROJECT_BOARD/` directory contains:
- **1 Epic** describing the overall TDD roadmap
- **23 Story templates** organized into 5 phases
- **3 Documentation files** (README, LABELS, KANBAN_STRUCTURE)
- **2 Helper scripts** for automation

## Quick Start (3 Steps)

### Step 1: Create Labels (5 minutes)

Run the label creation script:

```bash
cd .github/PROJECT_BOARD
./create_labels.sh
```

This creates all necessary labels in your GitHub repository:
- Phase labels (phase-1 through phase-5)
- Category labels (test-first, protocol, app-layer, etc.)
- Priority labels (priority-high, medium, low)
- Technology labels (crc16, serialization, command-parser, etc.)

**Alternative:** Manually create labels using GitHub's web interface following `LABELS.md`.

### Step 2: Create GitHub Project Board (10 minutes)

1. Go to your repository on GitHub
2. Click **Projects** tab
3. Click **New project**
4. Choose **Board** template
5. Name it: "Embedded Telemetry TDD Roadmap"
6. Configure columns as described in `KANBAN_STRUCTURE.md`:
   - Backlog
   - Ready
   - In Progress
   - Testing
   - Review
   - Done

7. Create additional views:
   - **Phase View**: Group by phase-* labels
   - **Priority View**: Group by priority-* labels
   - **Roadmap View**: Timeline view with dates

### Step 3: Create Issues (5-10 minutes)

Run the issue creation script:

```bash
cd .github/PROJECT_BOARD
./create_issues.sh
```

This creates all 24 issues (1 epic + 23 stories) in your repository with:
- Proper titles with phase prefixes
- Complete descriptions from markdown templates
- Appropriate labels automatically applied

**Alternative:** Manually create issues using GitHub's web interface, copying content from each `.md` file.

## Manual Issue Creation (if scripts don't work)

If you can't use the scripts, create issues manually:

### For Each Story File:

1. Go to GitHub Issues → New Issue
2. Copy the title format: `[Phase N] Story Title`
3. Copy the entire markdown content as the issue body
4. Add labels listed in the `**Labels:**` line of the story
5. Assign to the appropriate milestone (e.g., "Phase 1 - CRC16")
6. Add to your project board

### Example:

For file `PHASE-1-CRC16/01-crc16-empty-buffer-test.md`:

- **Title:** `[Phase 1] Implement CRC16 Empty Buffer Test`
- **Body:** Copy entire markdown content
- **Labels:** `phase-1`, `test-first`, `protocol`, `crc16`
- **Milestone:** Phase 1 - CRC16 Implementation
- **Project:** Embedded Telemetry TDD Roadmap

## Organization Tips

### Create Milestones

Create 5 milestones, one for each phase:

1. **Phase 1 - CRC16 Implementation** (5 issues)
2. **Phase 2 - Packet Serialization** (5 issues)
3. **Phase 3 - Command Parser** (5 issues)
4. **Phase 4 - Device Integration** (4 issues)
5. **Phase 5 - CI/CD Automation** (4 issues)

### Link Dependencies

Edit issues to add dependency links:

```markdown
## Dependencies
- Depends on: #123 (Previous story)
- Blocks: #125 (Next story)
```

### Add to Project Board

After creating issues:
1. Go to your project board
2. Click **+ Add item**
3. Search for and add each issue
4. Drag issues to "Backlog" column
5. Move Phase 1 stories to "Ready" column

## Working Through the Roadmap

### Phase-by-Phase Approach

Work through phases in order:

1. **Phase 1 (CRC16)** - Start here, no dependencies
2. **Phase 2 (Packet)** - After Phase 1 complete
3. **Phase 3 (Parser)** - After Phase 2 complete
4. **Phase 4 (Device)** - After Phase 3 complete
5. **Phase 5 (CI/CD)** - Can start after Phases 1-3

### For Each Story

1. **Move to "In Progress"** - Drag issue card
2. **Read Acceptance Criteria** - Know what tests must pass
3. **Write Tests First** - Following TDD approach
4. **Implement Code** - Make tests pass
5. **Move to "Testing"** - Run all tests
6. **Move to "Review"** - Create PR
7. **Move to "Done"** - After PR merged

### Test-Driven Development Flow

Each story follows this pattern:

```bash
# 1. Write tests first (they should fail)
platformio test -e native -f test_crc16_empty_buffer
# FAIL - no implementation yet

# 2. Implement minimum code to pass tests
# Edit firmware/lib/protocol/crc16.c

# 3. Run tests again
platformio test -e native
# PASS - implementation correct

# 4. Verify device build
platformio run -e rpipico2w
# Build successful

# 5. Commit and push
git add .
git commit -m "[Phase 1] Implement CRC16 empty buffer handling"
git push

# 6. Create PR and link to issue
```

## Tracking Progress

### In GitHub Project Board

- **Velocity:** Track stories completed per week
- **Burndown:** Watch stories moving to "Done"
- **Blockers:** Mark issues with `status-blocked` label

### In README

Update project README with:
- Current phase
- Completed stories count (e.g., "Phase 1: 3/5 complete")
- Link to project board

## Customization

### Modify Stories

The story templates are just starting points. Feel free to:
- Adjust time estimates based on your experience
- Add more acceptance criteria
- Split stories into smaller tasks
- Add technical notes specific to your implementation

### Add New Stories

If you need additional stories:
1. Copy an existing story template
2. Modify the content
3. Follow the same structure:
   - User Story
   - Acceptance Criteria
   - Implementation Tasks
   - Technical Notes
   - Definition of Done
   - Related Issues
   - References

### Skip Phases

If you don't need certain phases:
- You can skip Phase 4 (Device Integration) if you don't have hardware yet
- Phase 5 (CI/CD) can be implemented later
- Phases 1-3 should be completed in order

## Common Issues

### Scripts Don't Run

- **Issue:** Permission denied
- **Fix:** `chmod +x create_*.sh`

- **Issue:** GitHub CLI not found
- **Fix:** Install from https://cli.github.com/

- **Issue:** Not authenticated
- **Fix:** Run `gh auth login`

### Too Many Issues

- **Issue:** 23+ stories is overwhelming
- **Fix:** Focus on one phase at a time. Hide completed phases in project board.

### Dependencies Not Clear

- **Issue:** Don't know which story to start
- **Fix:** Follow the numbering within each phase. Phase 1, Story 01 is the starting point.

## Next Steps

After setting up the project board:

1. ✅ **Start Phase 1, Story 01**: CRC16 Empty Buffer Test
2. ✅ **Follow TDD Workflow**: Write tests, implement, verify
3. ✅ **Track Progress**: Move issues through board columns
4. ✅ **Commit Regularly**: Small, focused commits
5. ✅ **Complete Phases**: One at a time, in order

## Getting Help

- Read `README.md` in this directory for full documentation
- Check `LABELS.md` for label definitions
- Review `KANBAN_STRUCTURE.md` for board organization
- Look at individual story files for detailed guidance
- Refer to project docs in `docs/TESTING.md` for testing strategy

---

**Ready to start?** Run the setup scripts and begin with Phase 1, Story 01! 🚀
