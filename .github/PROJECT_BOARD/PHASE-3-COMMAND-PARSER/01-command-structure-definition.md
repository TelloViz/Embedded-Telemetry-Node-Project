# Story: Define Command Structure and Types

**Type:** Story  
**Phase:** 3 - Command Parser  
**Status:** Open  
**Priority:** High  
**Estimation:** 3 hours  
**Labels:** `test-first`, `protocol`, `command-parser`, `phase-3`

## User Story

As a developer, I need to define command structures and types, so that the telemetry node can receive and process remote commands.

## Acceptance Criteria

- [ ] `test_command_structure_size` passes - verifies command structure layout
- [ ] `test_command_types_defined` passes - verifies all command types are defined
- [ ] `test_command_id_uniqueness` passes - verifies command IDs are unique
- [ ] Tests run on native platform (`platformio test -e native`)
- [ ] Tests are in `test/test_protocol.cpp`

## Implementation Tasks

1. [ ] Define command structure in `firmware/lib/protocol/command.h`:
   ```cpp
   #ifndef COMMAND_H
   #define COMMAND_H
   
   #include <stdint.h>
   #include <stdbool.h>
   
   // Command IDs
   typedef enum {
       CMD_PING = 0x01,              // Ping (health check)
       CMD_GET_STATUS = 0x02,         // Get system status
       CMD_SET_TELEMETRY_PERIOD = 0x03, // Set telemetry period (ms)
       CMD_GET_TELEMETRY_PERIOD = 0x04, // Get telemetry period
       CMD_RESET = 0x05,              // Reset system
       CMD_GET_VERSION = 0x06         // Get firmware version
   } command_id_t;
   
   // Command structure (embedded in packet payload)
   typedef struct __attribute__((packed)) {
       uint8_t command_id;            // command_id_t
       uint8_t param_count;           // Number of parameters
       uint8_t params[8];             // Up to 8 parameter bytes
   } command_t;
   
   // Response codes
   typedef enum {
       RESP_OK = 0x00,
       RESP_ERROR = 0x01,
       RESP_INVALID_CMD = 0x02,
       RESP_INVALID_PARAM = 0x03
   } response_code_t;
   
   // Response structure
   typedef struct __attribute__((packed)) {
       uint8_t command_id;            // Echo of command ID
       uint8_t response_code;         // response_code_t
       uint8_t data_count;            // Number of data bytes
       uint8_t data[16];              // Response data
   } response_t;
   
   #endif
   ```

2. [ ] Write structure tests in `test/test_protocol.cpp`:
   ```cpp
   void test_command_structure_size(void) {
       TEST_ASSERT_EQUAL(10, sizeof(command_t)); // 1 + 1 + 8
       TEST_ASSERT_EQUAL(19, sizeof(response_t)); // 1 + 1 + 1 + 16
   }
   
   void test_command_types_defined(void) {
       TEST_ASSERT_EQUAL(0x01, CMD_PING);
       TEST_ASSERT_EQUAL(0x02, CMD_GET_STATUS);
       TEST_ASSERT_EQUAL(0x03, CMD_SET_TELEMETRY_PERIOD);
       TEST_ASSERT_EQUAL(0x04, CMD_GET_TELEMETRY_PERIOD);
       TEST_ASSERT_EQUAL(0x05, CMD_RESET);
       TEST_ASSERT_EQUAL(0x06, CMD_GET_VERSION);
   }
   
   void test_command_id_uniqueness(void) {
       // Ensure all command IDs are unique
       uint8_t ids[] = {
           CMD_PING,
           CMD_GET_STATUS,
           CMD_SET_TELEMETRY_PERIOD,
           CMD_GET_TELEMETRY_PERIOD,
           CMD_RESET,
           CMD_GET_VERSION
       };
       
       for (int i = 0; i < 6; i++) {
           for (int j = i + 1; j < 6; j++) {
               TEST_ASSERT_NOT_EQUAL(ids[i], ids[j]);
           }
       }
   }
   ```

3. [ ] Add test runner entries

4. [ ] Run tests: `platformio test -e native -f test_command*`

5. [ ] Verify tests pass

6. [ ] Verify firmware builds: `platformio run -e rpipico2w`

## Technical Notes

- **Command Format:**
  - Command ID: identifies the operation
  - Parameter count: number of valid parameter bytes
  - Parameters: up to 8 bytes of command-specific data

- **Response Format:**
  - Echo command ID: links response to command
  - Response code: success/error indication
  - Data count: number of valid response data bytes
  - Data: up to 16 bytes of response data

- **Design Decisions:**
  - Fixed-size structures for predictable memory usage
  - Packed structures for wire format compatibility
  - Sufficient parameter/data space for most commands

## Definition of Done

- [ ] Command and response structures defined
- [ ] Command IDs enumerated
- [ ] Response codes enumerated
- [ ] All structure tests pass
- [ ] All tests pass on native platform
- [ ] Code compiles for target device (rpipico2w)
- [ ] No compiler warnings

## Related Issues

- Epic: #[EPIC-NUMBER] - TDD Roadmap
- Depends on: Phase 2 - Endianness Handling
- Blocks: Story #[NEXT] - Command Parser Implementation

## References

- File: `test/test_protocol.cpp`
- File: `firmware/lib/protocol/command.h`
- Docs: [TESTING.md](../../docs/TESTING.md)
