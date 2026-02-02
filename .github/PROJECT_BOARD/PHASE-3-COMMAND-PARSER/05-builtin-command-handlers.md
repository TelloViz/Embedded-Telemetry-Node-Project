# Story: Implement Built-in Command Handlers

**Type:** Story  
**Phase:** 3 - Command Parser  
**Status:** Open  
**Priority:** Medium  
**Estimation:** 4 hours  
**Labels:** `test-first`, `protocol`, `command-parser`, `phase-3`, `app-layer`

## User Story

As a developer, I need built-in handlers for common commands (PING, GET_STATUS, etc.), so that the telemetry node responds to basic queries.

## Acceptance Criteria

- [ ] `test_handle_ping` passes - PING command returns PONG
- [ ] `test_handle_get_status` passes - GET_STATUS returns system state
- [ ] `test_handle_set_telemetry_period` passes - sets telemetry period
- [ ] `test_handle_get_version` passes - returns firmware version
- [ ] Tests run on native platform (`platformio test -e native`)

## Implementation Tasks

1. [ ] Implement PING handler
2. [ ] Implement GET_STATUS handler  
3. [ ] Implement SET_TELEMETRY_PERIOD handler
4. [ ] Implement GET_VERSION handler
5. [ ] Write tests for each handler
6. [ ] Integrate handlers with dispatcher
7. [ ] Verify all tests pass

**Estimation:** 4 hours

**Note:** This completes Phase 3 (Command Parser).
