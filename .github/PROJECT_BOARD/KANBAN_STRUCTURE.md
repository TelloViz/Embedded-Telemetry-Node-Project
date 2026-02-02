# Project Kanban Board Structure

This document describes the recommended kanban board structure for tracking the TDD workflow.

## GitHub Projects Setup

Create a GitHub Project (Projects tab in repository) with the following structure:

### Board Name
**Embedded Telemetry TDD Roadmap**

### Views

#### 1. Kanban View (Primary)

**Columns:**
- **Backlog** - Stories not yet started
- **Ready** - Stories ready to begin (dependencies met)
- **In Progress** - Currently being worked on
- **Testing** - Implementation complete, tests running
- **Review** - Ready for code review
- **Done** - Completed and merged

#### 2. Phase View (Grouped by Phase)

Group issues by `phase-*` label to see progress per phase:
- Phase 1: CRC16 Implementation
- Phase 2: Packet Serialization
- Phase 3: Command Parser
- Phase 4: Device Integration
- Phase 5: CI/CD Automation

#### 3. Priority View (Grouped by Priority)

Group issues by `priority-*` label to focus on high-priority items first.

#### 4. Roadmap View (Timeline)

Use GitHub Projects timeline view to visualize:
- Start date
- End date (based on estimation)
- Dependencies between stories

## Workflow States

### Backlog
- All stories start here
- Awaiting dependencies or prioritization
- Not actively being worked on

### Ready
- All dependencies met
- Tests defined
- Ready to begin implementation
- Acceptance criteria clear

### In Progress
- Developer actively working
- Tests written or being written
- Implementation in progress

### Testing
- Implementation complete
- Tests running (native or device)
- Verifying acceptance criteria
- May require iteration if tests fail

### Review
- All tests passing
- Code ready for peer review
- PR created and waiting for approval

### Done
- Code reviewed and approved
- PR merged to main branch
- Tests passing in CI/CD
- Documentation updated

## Issue Templates

When creating issues from the story files in this directory, include:

### Title Format
```
[Phase N] Story Title
```
Example: `[Phase 1] Implement CRC16 Empty Buffer Test`

### Description Template
Use the markdown content from the story file as the issue description.

### Labels
Apply relevant labels as defined in LABELS.md

### Assignees
Assign to developer(s) working on the story

### Milestone
Create milestones for each phase:
- Milestone: Phase 1 - CRC16 Implementation
- Milestone: Phase 2 - Packet Serialization
- Milestone: Phase 3 - Command Parser
- Milestone: Phase 4 - Device Integration
- Milestone: Phase 5 - CI/CD Automation

### Projects
Add to the "Embedded Telemetry TDD Roadmap" project

## Dependencies

Use GitHub's task lists and issue references to track dependencies:

```markdown
## Depends On
- Depends on: #123 (Previous story)

## Blocks
- Blocks: #125 (Next story)
```

## Automation

Set up GitHub Actions or Project automation for:

1. **Auto-add to project**: New issues with `phase-*` labels automatically added to project
2. **Auto-move to "In Progress"**: Issues move when PR is opened
3. **Auto-move to "Review"**: Issues move when PR is marked ready for review
4. **Auto-move to "Done"**: Issues move and close when PR is merged

## Metrics

Track these metrics in the project:

- **Velocity**: Stories completed per week
- **Lead Time**: Time from "Ready" to "Done"
- **Cycle Time**: Time from "In Progress" to "Done"
- **Phase Progress**: Percentage of stories completed per phase
- **Test Coverage**: Code coverage percentage (from CI/CD)

## Example Board URL Structure

```
https://github.com/TelloViz/Embedded-Telemetry-Node-Project/projects/1
```

## Updating the Board

As you work through stories:

1. Move issue to appropriate column
2. Update task checkboxes in issue description
3. Add comments on progress or blockers
4. Link related PRs to the issue
5. Close issue when all acceptance criteria met and PR merged
