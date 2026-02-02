# Story: GitHub Actions - Automated Builds

**Type:** Story  
**Phase:** 5 - CI/CD Automation  
**Status:** Open  
**Priority:** High  
**Estimation:** 3 hours  
**Labels:** `ci-cd`, `automation`, `github-actions`, `phase-5`

## User Story

As a developer, I need automated firmware builds in CI/CD pipeline, so that build failures are caught early.

## Acceptance Criteria

- [ ] GitHub Actions workflow builds firmware for rpipico2w
- [ ] Workflow runs on every PR
- [ ] Workflow fails if build fails
- [ ] Build artifacts are available for download
- [ ] Workflow is in `.github/workflows/build.yml`

## Implementation Tasks

1. [ ] Create `.github/workflows/build.yml`
2. [ ] Add build step for rpipico2w target
3. [ ] Upload firmware binary as artifact
4. [ ] Test workflow
5. [ ] Document build process

**Estimation:** 3 hours
