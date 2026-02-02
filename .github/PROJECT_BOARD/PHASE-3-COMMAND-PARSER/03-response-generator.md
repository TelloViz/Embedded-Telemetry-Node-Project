# Story: Implement Response Generator

**Type:** Story  
**Phase:** 3 - Command Parser  
**Status:** Open  
**Priority:** High  
**Estimation:** 4 hours  
**Labels:** `test-first`, `protocol`, `command-parser`, `phase-3`

## User Story

As a developer, I need to generate response structures for executed commands, so that the host can receive acknowledgments and data.

## Acceptance Criteria

- [ ] `test_generate_response_ok` passes - generates OK response
- [ ] `test_generate_response_with_data` passes - generates response with data payload
- [ ] `test_generate_response_error` passes - generates error response
- [ ] Tests run on native platform (`platformio test -e native`)

## Implementation Tasks

1. [ ] Add response generator API to `firmware/lib/protocol/command.h`
2. [ ] Implement generator in `firmware/lib/protocol/command.c`
3. [ ] Write tests for all response types
4. [ ] Verify tests pass

**Estimation:** 4 hours
