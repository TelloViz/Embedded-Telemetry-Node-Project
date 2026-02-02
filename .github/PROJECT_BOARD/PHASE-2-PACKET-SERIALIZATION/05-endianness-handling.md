# Story: Implement Endianness Handling

**Type:** Story  
**Phase:** 2 - Packet Serialization  
**Status:** Open  
**Priority:** Medium  
**Estimation:** 3 hours  
**Labels:** `test-first`, `protocol`, `serialization`, `phase-2`, `portability`

## User Story

As a developer, I need consistent endianness handling for multi-byte fields, so that packets are portable across different architectures (ARM, x86, etc.).

## Acceptance Criteria

- [ ] `test_serialize_uint16_big_endian` passes - verifies 16-bit values are big-endian
- [ ] `test_serialize_uint32_big_endian` passes - verifies 32-bit values are big-endian
- [ ] `test_deserialize_uint16_big_endian` passes - reads big-endian 16-bit values
- [ ] `test_deserialize_uint32_big_endian` passes - reads big-endian 32-bit values
- [ ] `test_endianness_roundtrip` passes - serialize then deserialize preserves values
- [ ] Tests run on native platform (`platformio test -e native`)
- [ ] Tests are in `test/test_protocol.cpp`

## Implementation Tasks

1. [ ] Add endianness utilities to `firmware/lib/protocol/endian.h`:
   ```cpp
   #ifndef ENDIAN_H
   #define ENDIAN_H
   
   #include <stdint.h>
   
   // Serialize multi-byte values to big-endian
   void write_uint16_be(uint8_t* buffer, uint16_t value);
   void write_uint32_be(uint8_t* buffer, uint32_t value);
   
   // Deserialize multi-byte values from big-endian
   uint16_t read_uint16_be(const uint8_t* buffer);
   uint32_t read_uint32_be(const uint8_t* buffer);
   
   #endif
   ```

2. [ ] Implement endianness functions in `firmware/lib/protocol/endian.c`:
   ```cpp
   void write_uint16_be(uint8_t* buffer, uint16_t value) {
       buffer[0] = (value >> 8) & 0xFF;  // MSB
       buffer[1] = value & 0xFF;          // LSB
   }
   
   void write_uint32_be(uint8_t* buffer, uint32_t value) {
       buffer[0] = (value >> 24) & 0xFF;
       buffer[1] = (value >> 16) & 0xFF;
       buffer[2] = (value >> 8) & 0xFF;
       buffer[3] = value & 0xFF;
   }
   
   uint16_t read_uint16_be(const uint8_t* buffer) {
       return ((uint16_t)buffer[0] << 8) | buffer[1];
   }
   
   uint32_t read_uint32_be(const uint8_t* buffer) {
       return ((uint32_t)buffer[0] << 24) |
              ((uint32_t)buffer[1] << 16) |
              ((uint32_t)buffer[2] << 8) |
              buffer[3];
   }
   ```

3. [ ] Write endianness tests in `test/test_protocol.cpp`:
   ```cpp
   void test_serialize_uint16_big_endian(void) {
       uint8_t buffer[2];
       write_uint16_be(buffer, 0x1234);
       
       TEST_ASSERT_EQUAL_HEX8(0x12, buffer[0]); // MSB first
       TEST_ASSERT_EQUAL_HEX8(0x34, buffer[1]); // LSB second
   }
   
   void test_serialize_uint32_big_endian(void) {
       uint8_t buffer[4];
       write_uint32_be(buffer, 0x12345678);
       
       TEST_ASSERT_EQUAL_HEX8(0x12, buffer[0]);
       TEST_ASSERT_EQUAL_HEX8(0x34, buffer[1]);
       TEST_ASSERT_EQUAL_HEX8(0x56, buffer[2]);
       TEST_ASSERT_EQUAL_HEX8(0x78, buffer[3]);
   }
   
   void test_deserialize_uint16_big_endian(void) {
       uint8_t buffer[] = {0xAB, 0xCD};
       uint16_t value = read_uint16_be(buffer);
       
       TEST_ASSERT_EQUAL_HEX16(0xABCD, value);
   }
   
   void test_deserialize_uint32_big_endian(void) {
       uint8_t buffer[] = {0x12, 0x34, 0x56, 0x78};
       uint32_t value = read_uint32_be(buffer);
       
       TEST_ASSERT_EQUAL_HEX32(0x12345678, value);
   }
   
   void test_endianness_roundtrip(void) {
       uint8_t buffer[4];
       uint16_t test16 = 0xBEEF;
       uint32_t test32 = 0xDEADBEEF;
       
       // 16-bit roundtrip
       write_uint16_be(buffer, test16);
       uint16_t read16 = read_uint16_be(buffer);
       TEST_ASSERT_EQUAL_HEX16(test16, read16);
       
       // 32-bit roundtrip
       write_uint32_be(buffer, test32);
       uint32_t read32 = read_uint32_be(buffer);
       TEST_ASSERT_EQUAL_HEX32(test32, read32);
   }
   ```

4. [ ] Update `packet.c` to use endian functions for CRC field

5. [ ] Add test runner entries

6. [ ] Run tests: `platformio test -e native -f test_*endian*`

7. [ ] Verify all tests pass

8. [ ] Verify firmware builds: `platformio run -e rpipico2w`

## Technical Notes

- **Big-Endian Format:**
  - Network byte order (most significant byte first)
  - Platform-independent representation
  - Standard for network protocols

- **Why Big-Endian:**
  - Network protocols traditionally use big-endian
  - Makes binary dumps human-readable
  - Consistent across ARM (Pico) and x86 (native tests)

- **Usage in Packet:**
  - CRC16 field stored as big-endian
  - Future multi-byte fields (timestamps, values) use big-endian
  - Single-byte fields (magic, version, type, length) unaffected

## Definition of Done

- [ ] Endianness utility functions implemented
- [ ] All endianness tests pass
- [ ] Packet serialization uses endian functions
- [ ] Roundtrip tests verify correctness
- [ ] All tests pass on native platform
- [ ] Code compiles for target device (rpipico2w)
- [ ] No compiler warnings

## Related Issues

- Epic: #[EPIC-NUMBER] - TDD Roadmap
- Depends on: Story #[PREV] - Packet Buffer Management
- Blocks: Phase 3 - Command Parser

## References

- File: `test/test_protocol.cpp`
- File: `firmware/lib/protocol/endian.h`
- File: `firmware/lib/protocol/endian.c`
- File: `firmware/lib/protocol/packet.c`
- Docs: [TESTING.md](../../docs/TESTING.md)

## Notes

This story completes Phase 2 (Packet Serialization). After this:
- Complete packet serialization/deserialization is functional
- Endianness is handled correctly for portability
- Buffer management is efficient
- Ready to implement command parsing in Phase 3
