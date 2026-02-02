# Story: Implement CRC16 Known Value Test

**Type:** Story  
**Phase:** 1 - Protocol Layer (CRC16)  
**Status:** Open  
**Priority:** High  
**Estimation:** 3 hours  
**Labels:** `test-first`, `protocol`, `crc16`, `phase-1`

## User Story

As a developer, I need to verify that CRC16 computation produces correct checksums for known test vectors, so that I can be confident the algorithm is implemented correctly.

## Acceptance Criteria

- [ ] `test_crc16_known_value` passes - verifies CRC of "123456789" returns expected value
- [ ] `test_crc16_hello_world` passes - verifies CRC of "Hello, World!" returns expected value
- [ ] Tests run on native platform (`platformio test -e native`)
- [ ] Tests are in `test/test_protocol.cpp`

## Implementation Tasks

1. [ ] Write unit tests in `test/test_protocol.cpp`:
   ```cpp
   void test_crc16_known_value(void) {
       const uint8_t data[] = "123456789";
       uint16_t result = crc16_compute(data, 9);
       // CRC-16/XMODEM of "123456789" = 0x31C3
       TEST_ASSERT_EQUAL_HEX16(0x31C3, result);
   }
   
   void test_crc16_hello_world(void) {
       const uint8_t data[] = "Hello, World!";
       uint16_t result = crc16_compute(data, 13);
       // CRC-16/XMODEM of "Hello, World!" = 0x374B
       TEST_ASSERT_EQUAL_HEX16(0x374B, result);
   }
   ```

2. [ ] Implement complete CRC16 algorithm in `firmware/lib/protocol/crc16.c`:
   - Use lookup table or direct computation
   - CRC-16/XMODEM: polynomial 0x1021, initial 0xFFFF, no final XOR

3. [ ] Add test runner entries in `test/test_protocol.cpp`:
   ```cpp
   RUN_TEST(test_crc16_empty_buffer);
   RUN_TEST(test_crc16_known_value);
   RUN_TEST(test_crc16_hello_world);
   ```

4. [ ] Run tests: `platformio test -e native -f test_crc16*`

5. [ ] Verify all CRC16 tests pass

6. [ ] Verify firmware builds: `platformio run -e rpipico2w`

## Technical Notes

- **CRC-16/XMODEM Specification:**
  - Polynomial: 0x1021 (x^16 + x^12 + x^5 + 1)
  - Initial value: 0xFFFF
  - Reflect input: false
  - Reflect output: false
  - Final XOR: 0x0000

- **Test Vectors (verified):**
  - "123456789" → 0x31C3
  - "Hello, World!" → 0x374B

- **Implementation Options:**
  - Table-driven (faster, uses 512 bytes)
  - Bit-by-bit (slower, minimal memory)
  - Recommend table-driven for embedded performance

## Definition of Done

- [ ] All tests written and documented
- [ ] All tests pass on native platform
- [ ] Code compiles for target device (rpipico2w)
- [ ] Code follows project style guidelines
- [ ] No compiler warnings
- [ ] Test vectors match standard CRC-16/XMODEM

## Related Issues

- Epic: #[EPIC-NUMBER] - TDD Roadmap
- Depends on: Story #[PREV] - CRC16 Empty Buffer Test
- Blocks: Story #[NEXT] - CRC16 Edge Cases Test

## References

- File: `test/test_protocol.cpp`
- File: `firmware/lib/protocol/crc16.c`
- Standard: CRC-16/XMODEM
- Verification tool: https://crccalc.com/
