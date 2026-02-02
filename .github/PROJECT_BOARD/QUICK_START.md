# Quick Start - 3 Steps to Get Your Issues Created

This is the fastest way to set up your TDD project board and issues.

## Prerequisites

- GitHub CLI (`gh`) installed: https://cli.github.com/
- Authenticated with your GitHub account: `gh auth login`
- Repository cloned locally

## Step 1: Create Labels (1 minute)

```bash
cd .github/PROJECT_BOARD
./create_labels.sh
```

Output:
```
🏷️  Creating GitHub labels...
✅ Created: phase-1
✅ Created: test-first
...
🎉 All labels created successfully!
```

## Step 2: Create Issues (1 minute)

```bash
./create_issues.sh
```

Output:
```
🚀 Creating GitHub issues...
✅ Epic created
✅ Phase 1 issues created (5 issues)
✅ Phase 2 issues created (5 issues)
...
🎉 All issues created successfully!
```

## Step 3: Set Up Project Board (5 minutes)

### Option A: Use GitHub's Web Interface

1. Go to your repository on GitHub
2. Click **Projects** → **New project**
3. Choose **Board** template
4. Name it: "Embedded Telemetry TDD Roadmap"
5. Add these columns:
   - Backlog
   - Ready
   - In Progress
   - Testing
   - Review
   - Done
6. Click **+ Add item** and add all your newly created issues

### Option B: Use GitHub CLI

```bash
# Create project
gh project create "Embedded Telemetry TDD Roadmap" --owner TelloViz

# Add all issues to project (replace PROJECT_NUMBER with your project number)
gh project item-add PROJECT_NUMBER --owner TelloViz --url https://github.com/TelloViz/Embedded-Telemetry-Node-Project/issues/ISSUE_NUMBER
```

## That's It! 🎉

You now have:
- ✅ 24 issues (1 epic + 23 stories)
- ✅ All labels configured
- ✅ Project board ready to use

## Next Steps

1. **Organize Issues:** Drag Phase 1 issues to "Ready" column
2. **Create Milestones:** One for each phase
3. **Start Coding:** Begin with `[Phase 1] Implement CRC16 Empty Buffer Test`

## If Scripts Don't Work

See `USAGE_GUIDE.md` for manual instructions.

## Resources

- `README.md` - Full documentation
- `USAGE_GUIDE.md` - Detailed setup guide
- `KANBAN_STRUCTURE.md` - Project board organization
- `LABELS.md` - Label definitions

---

**Ready to code?** Start with Phase 1, Story 01 and follow the TDD workflow! 🚀
