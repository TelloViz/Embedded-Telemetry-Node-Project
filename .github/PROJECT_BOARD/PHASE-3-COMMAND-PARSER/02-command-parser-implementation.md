# Story: Implement Command Parser

**Type:** Story  
**Phase:** 3 - Command Parser  
**Status:** Open  
**Priority:** High  
**Estimation:** 5 hours  
**Labels:** `test-first`, `protocol`, `command-parser`, `phase-3`

## User Story

As a developer, I need to parse command structures from packet payloads, so that the telemetry node can execute received commands.

## Acceptance Criteria

- [ ] `test_parse_command_ping` passes - parses PING command correctly
- [ ] `test_parse_command_with_params` passes - parses commands with parameters
- [ ] `test_parse_invalid_command` passes - rejects invalid command IDs
- [ ] `test_parse_command_buffer_size` passes - validates buffer sizes
- [ ] Tests run on native platform (`platformio test -e native`)
- [ ] Tests are in `test/test_protocol.cpp`

## Implementation Tasks

1. [ ] Add command parser API to `firmware/lib/protocol/command.h`:
   ```cpp
   // Parse command from packet payload
   bool command_parse(command_t* cmd, const uint8_t* payload, size_t length);
   
   // Validate command structure
   bool command_validate(const command_t* cmd);
   ```

2. [ ] Implement parser in `firmware/lib/protocol/command.c`

3. [ ] Write parser tests in `test/test_protocol.cpp`

4. [ ] Run tests and verify

## Technical Notes

Parser must:
- Extract command_id, param_count, and params from payload
- Validate command_id is in valid range
- Validate param_count ≤ 8
- Validate buffer size is sufficient
- Return false on any validation error

**Estimation:** 5 hours
