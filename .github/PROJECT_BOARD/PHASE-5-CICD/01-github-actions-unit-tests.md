# Story: GitHub Actions - Automated Unit Tests

**Type:** Story  
**Phase:** 5 - CI/CD Automation  
**Status:** Open  
**Priority:** High  
**Estimation:** 4 hours  
**Labels:** `ci-cd`, `automation`, `github-actions`, `phase-5`

## User Story

As a developer, I need automated unit tests in CI/CD pipeline, so that every PR is validated before merge.

## Acceptance Criteria

- [ ] GitHub Actions workflow runs on every PR
- [ ] Workflow executes `platformio test -e native`
- [ ] Workflow fails if any test fails
- [ ] Test results are visible in PR status checks
- [ ] Workflow is in `.github/workflows/test.yml`

## Implementation Tasks

1. [ ] Create `.github/workflows/test.yml`:
   ```yaml
   name: Unit Tests
   
   on: [push, pull_request]
   
   jobs:
     test:
       runs-on: ubuntu-latest
       steps:
         - uses: actions/checkout@v3
         - uses: actions/setup-python@v4
           with:
             python-version: '3.x'
         - name: Install PlatformIO
           run: pip install platformio
         - name: Run Tests
           run: platformio test -e native
   ```

2. [ ] Test workflow on a sample PR
3. [ ] Verify tests run automatically
4. [ ] Document CI/CD setup

**Estimation:** 4 hours
