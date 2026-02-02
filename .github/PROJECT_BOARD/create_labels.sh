#!/bin/bash
# Script to create GitHub labels for the TDD workflow
# Requires: GitHub CLI (gh) installed and authenticated

set -e

REPO="TelloViz/Embedded-Telemetry-Node-Project"

echo "🏷️  Creating GitHub labels for Embedded Telemetry TDD Roadmap"
echo "Repository: $REPO"
echo ""

# Check if gh CLI is installed
if ! command -v gh &> /dev/null; then
    echo "❌ GitHub CLI (gh) is not installed."
    echo "Please install it from: https://cli.github.com/"
    exit 1
fi

# Check if authenticated
if ! gh auth status &> /dev/null; then
    echo "❌ Not authenticated with GitHub CLI."
    echo "Please run: gh auth login"
    exit 1
fi

echo "✅ GitHub CLI is installed and authenticated"
echo ""

# Function to create label (ignores if already exists)
create_label() {
    local name="$1"
    local description="$2"
    local color="$3"
    
    if gh label create "$name" --repo "$REPO" --description "$description" --color "$color" 2>/dev/null; then
        echo "  ✅ Created: $name"
    else
        echo "  ⚠️  Already exists: $name"
    fi
}

echo "📝 Creating Phase Labels..."
create_label "phase-1" "Phase 1: CRC16 Implementation" "0052CC"
create_label "phase-2" "Phase 2: Packet Serialization" "0065FF"
create_label "phase-3" "Phase 3: Command Parser" "0078FF"
create_label "phase-4" "Phase 4: Device Integration Tests" "008AFF"
create_label "phase-5" "Phase 5: CI/CD Automation" "009DFF"
echo ""

echo "📝 Creating Category Labels..."
create_label "test-first" "TDD approach - write tests first" "7057FF"
create_label "protocol" "Protocol layer implementation" "BFD4F2"
create_label "app-layer" "Application layer implementation" "C5DEF5"
create_label "device-test" "Device integration testing on hardware" "B60205"
create_label "ci-cd" "CI/CD pipeline and automation" "0E8A16"
create_label "automation" "General automation tasks" "1D76DB"
create_label "documentation" "Documentation updates" "0075CA"
echo ""

echo "📝 Creating Type Labels..."
create_label "epic" "Large, multi-phase initiative" "3E4B9E"
create_label "story" "User story (feature increment)" "5319E7"
create_label "task" "Individual task or subtask" "D4C5F9"
create_label "roadmap" "Roadmap and planning" "C2E0C6"
echo ""

echo "📝 Creating Priority Labels..."
create_label "priority-high" "High priority (must have)" "D73A4A"
create_label "priority-medium" "Medium priority (should have)" "FBCA04"
create_label "priority-low" "Low priority (nice to have)" "0E8A16"
echo ""

echo "📝 Creating Technology Labels..."
create_label "crc16" "CRC16 checksum implementation" "BFD4F2"
create_label "serialization" "Packet serialization/deserialization" "C2E0C6"
create_label "command-parser" "Command parsing and handling" "D4C5F9"
create_label "serial" "Serial communication" "E4E669"
create_label "integration" "Integration testing" "F9D0C4"
create_label "performance" "Performance and benchmarking" "FEF2C0"
create_label "reliability" "Error handling and recovery" "FFA8A8"
create_label "buffer-management" "Buffer and memory management" "C5DEF5"
create_label "portability" "Cross-platform portability" "BFD4F2"
create_label "optimization" "Performance optimization" "D4C5F9"
create_label "github-actions" "GitHub Actions workflows" "2088FF"
create_label "code-coverage" "Code coverage tracking" "0E8A16"
echo ""

echo "🎉 All labels created successfully!"
echo ""
echo "Next steps:"
echo "1. Run ./create_issues.sh to create issues"
echo "2. Set up GitHub Project board (see KANBAN_STRUCTURE.md)"
echo "3. Create milestones for each phase"
echo "4. Start implementing!"
