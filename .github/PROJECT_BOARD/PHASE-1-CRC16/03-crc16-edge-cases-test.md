# Story: Implement CRC16 Edge Cases Test

**Type:** Story  
**Phase:** 1 - Protocol Layer (CRC16)  
**Status:** Open  
**Priority:** Medium  
**Estimation:** 2 hours  
**Labels:** `test-first`, `protocol`, `crc16`, `phase-1`

## User Story

As a developer, I need to verify that CRC16 computation handles edge cases (single byte, maximum buffer, binary data) correctly, so that the telemetry protocol is robust in all scenarios.

## Acceptance Criteria

- [ ] `test_crc16_single_byte` passes - verifies CRC of 1-byte buffer
- [ ] `test_crc16_large_buffer` passes - verifies CRC of 1024-byte buffer
- [ ] `test_crc16_binary_data` passes - verifies CRC with null bytes in data
- [ ] All tests run on native platform (`platformio test -e native`)
- [ ] Tests are in `test/test_protocol.cpp`

## Implementation Tasks

1. [ ] Write edge case unit tests in `test/test_protocol.cpp`:
   ```cpp
   void test_crc16_single_byte(void) {
       const uint8_t data[] = {0x41}; // 'A'
       uint16_t result = crc16_compute(data, 1);
       TEST_ASSERT_NOT_EQUAL(0xFFFF, result); // Should be different from initial
   }
   
   void test_crc16_large_buffer(void) {
       uint8_t data[1024];
       for (int i = 0; i < 1024; i++) {
           data[i] = (uint8_t)(i & 0xFF);
       }
       uint16_t result = crc16_compute(data, 1024);
       TEST_ASSERT_NOT_EQUAL(0xFFFF, result);
       TEST_ASSERT_NOT_EQUAL(0x0000, result);
   }
   
   void test_crc16_binary_data(void) {
       const uint8_t data[] = {0x00, 0xFF, 0x00, 0xFF, 0x00};
       uint16_t result = crc16_compute(data, 5);
       TEST_ASSERT_NOT_EQUAL(0xFFFF, result);
   }
   ```

2. [ ] Verify CRC implementation handles:
   - Buffers of any size (1 to N bytes)
   - Binary data with null bytes
   - No buffer overruns

3. [ ] Add test runner entries in `test/test_protocol.cpp`

4. [ ] Run all CRC tests: `platformio test -e native -f test_crc16*`

5. [ ] Verify all tests pass

6. [ ] Verify firmware builds: `platformio run -e rpipico2w`

## Technical Notes

- **Edge Cases Covered:**
  - Minimum size: 1 byte
  - Large buffers: 1024 bytes (typical max packet size)
  - Binary data: includes null bytes (0x00)

- **Validation:**
  - CRC should never equal initial value (0xFFFF) for non-empty buffers
  - CRC should handle all byte values (0x00 to 0xFF)
  - No crashes, hangs, or buffer overruns

## Definition of Done

- [ ] All edge case tests written and documented
- [ ] All tests pass on native platform
- [ ] Code handles buffers from 1 to 1024+ bytes
- [ ] Code handles binary data with null bytes
- [ ] No compiler warnings
- [ ] No buffer overruns or memory issues

## Related Issues

- Epic: #[EPIC-NUMBER] - TDD Roadmap
- Depends on: Story #[PREV] - CRC16 Known Value Test
- Blocks: Story #[NEXT] - CRC16 Incremental Computation

## References

- File: `test/test_protocol.cpp`
- File: `firmware/lib/protocol/crc16.c`
- Docs: [TESTING.md](../../docs/TESTING.md)
