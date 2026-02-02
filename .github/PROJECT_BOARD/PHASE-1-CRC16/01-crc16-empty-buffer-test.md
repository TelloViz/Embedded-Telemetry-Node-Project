# Story: Implement CRC16 Empty Buffer Test

**Type:** Story  
**Phase:** 1 - Protocol Layer (CRC16)  
**Status:** Open  
**Priority:** High  
**Estimation:** 2 hours  
**Labels:** `test-first`, `protocol`, `crc16`, `phase-1`

## User Story

As a developer, I need to verify that CRC16 computation handles empty buffers correctly, so that edge cases don't cause crashes or undefined behavior in the telemetry protocol.

## Acceptance Criteria

- [ ] `test_crc16_empty_buffer` passes - verifies CRC of empty buffer returns 0xFFFF (or defined initial value)
- [ ] Test runs on native platform (`platformio test -e native`)
- [ ] Test is in `test/test_protocol.cpp`

## Implementation Tasks

1. [ ] Write unit test in `test/test_protocol.cpp`:
   ```cpp
   void test_crc16_empty_buffer(void) {
       uint16_t result = crc16_compute(NULL, 0);
       TEST_ASSERT_EQUAL_HEX16(0xFFFF, result); // Initial CRC value
   }
   ```

2. [ ] Create protocol library structure:
   ```bash
   mkdir -p firmware/lib/protocol
   touch firmware/lib/protocol/crc16.h
   touch firmware/lib/protocol/crc16.c
   ```

3. [ ] Implement minimal `crc16.h` interface:
   ```cpp
   #ifndef CRC16_H
   #define CRC16_H
   
   #include <stdint.h>
   #include <stddef.h>
   
   uint16_t crc16_compute(const uint8_t* data, size_t length);
   
   #endif
   ```

4. [ ] Implement empty buffer handling in `crc16.c`

5. [ ] Run test: `platformio test -e native -f test_crc16_empty_buffer`

6. [ ] Verify test passes

7. [ ] Verify firmware builds: `platformio run -e rpipico2w`

## Technical Notes

- CRC16 standard: Use CRC-16/XMODEM (polynomial 0x1021, initial value 0xFFFF)
- Empty buffer should return the initial CRC value without modification
- NULL pointer and length 0 should be handled safely

## Definition of Done

- [ ] Test written and documented
- [ ] Test passes on native platform
- [ ] Code compiles for target device (rpipico2w)
- [ ] Code follows project style guidelines
- [ ] No compiler warnings

## Related Issues

- Epic: #[EPIC-NUMBER] - TDD Roadmap
- Depends on: None (first story in Phase 1)
- Blocks: Story #[NEXT] - CRC16 Known Value Test

## References

- File: `test/test_protocol.cpp`
- File: `firmware/lib/protocol/crc16.h`
- File: `firmware/lib/protocol/crc16.c`
- Docs: [TESTING_QUICK_START.md](../../docs/TESTING_QUICK_START.md)
