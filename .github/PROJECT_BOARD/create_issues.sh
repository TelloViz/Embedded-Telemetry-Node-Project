#!/bin/bash
# Script to create GitHub issues from markdown templates
# Requires: GitHub CLI (gh) installed and authenticated

set -e

REPO="TelloViz/Embedded-Telemetry-Node-Project"
PROJECT_DIR=".github/PROJECT_BOARD"

echo "🚀 Creating GitHub issues for Embedded Telemetry TDD Roadmap"
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

# Function to extract title from markdown file
get_title() {
    local file="$1"
    local phase="$2"
    local number="$3"
    
    # Extract title from first markdown header
    local title=$(grep -m 1 "^# Story:" "$file" | sed 's/^# Story: //')
    
    # Add phase prefix
    echo "[Phase $phase] $title"
}

# Function to extract labels from markdown file
get_labels() {
    local file="$1"
    
    # Extract labels line
    local labels_line=$(grep "^**Labels:**" "$file" | sed 's/^**Labels:** //' | sed 's/`//g')
    
    echo "$labels_line"
}

# Create Epic
echo "📝 Creating Epic..."
gh issue create \
    --repo "$REPO" \
    --title "EPIC: Test-Driven Development Roadmap" \
    --body-file "$PROJECT_DIR/00-EPIC-TDD-ROADMAP.md" \
    --label "epic,test-first,roadmap"

echo "✅ Epic created"
echo ""

# Phase 1: CRC16
echo "📝 Creating Phase 1 issues (CRC16 Implementation)..."
for i in {1..5}; do
    file="$PROJECT_DIR/PHASE-1-CRC16/0$i-*.md"
    if [ -f $file ]; then
        title=$(get_title "$file" "1" "$i")
        labels=$(get_labels "$file")
        
        echo "  Creating: $title"
        gh issue create \
            --repo "$REPO" \
            --title "$title" \
            --body-file "$file" \
            --label "$labels"
    fi
done
echo "✅ Phase 1 issues created"
echo ""

# Phase 2: Packet Serialization
echo "📝 Creating Phase 2 issues (Packet Serialization)..."
for i in {1..5}; do
    file="$PROJECT_DIR/PHASE-2-PACKET-SERIALIZATION/0$i-*.md"
    if [ -f $file ]; then
        title=$(get_title "$file" "2" "$i")
        labels=$(get_labels "$file")
        
        echo "  Creating: $title"
        gh issue create \
            --repo "$REPO" \
            --title "$title" \
            --body-file "$file" \
            --label "$labels"
    fi
done
echo "✅ Phase 2 issues created"
echo ""

# Phase 3: Command Parser
echo "📝 Creating Phase 3 issues (Command Parser)..."
for i in {1..5}; do
    file="$PROJECT_DIR/PHASE-3-COMMAND-PARSER/0$i-*.md"
    if [ -f $file ]; then
        title=$(get_title "$file" "3" "$i")
        labels=$(get_labels "$file")
        
        echo "  Creating: $title"
        gh issue create \
            --repo "$REPO" \
            --title "$title" \
            --body-file "$file" \
            --label "$labels"
    fi
done
echo "✅ Phase 3 issues created"
echo ""

# Phase 4: Device Integration
echo "📝 Creating Phase 4 issues (Device Integration)..."
for i in {1..4}; do
    file="$PROJECT_DIR/PHASE-4-DEVICE-INTEGRATION/0$i-*.md"
    if [ -f $file ]; then
        title=$(get_title "$file" "4" "$i")
        labels=$(get_labels "$file")
        
        echo "  Creating: $title"
        gh issue create \
            --repo "$REPO" \
            --title "$title" \
            --body-file "$file" \
            --label "$labels"
    fi
done
echo "✅ Phase 4 issues created"
echo ""

# Phase 5: CI/CD
echo "📝 Creating Phase 5 issues (CI/CD Automation)..."
for i in {1..4}; do
    file="$PROJECT_DIR/PHASE-5-CICD/0$i-*.md"
    if [ -f $file ]; then
        title=$(get_title "$file" "5" "$i")
        labels=$(get_labels "$file")
        
        echo "  Creating: $title"
        gh issue create \
            --repo "$REPO" \
            --title "$title" \
            --body-file "$file" \
            --label "$labels"
    fi
done
echo "✅ Phase 5 issues created"
echo ""

echo "🎉 All issues created successfully!"
echo ""
echo "Next steps:"
echo "1. Create GitHub labels using LABELS.md"
echo "2. Set up GitHub Project board using KANBAN_STRUCTURE.md"
echo "3. Organize issues into milestones (one per phase)"
echo "4. Add issues to your project board"
echo "5. Start implementing Phase 1!"
