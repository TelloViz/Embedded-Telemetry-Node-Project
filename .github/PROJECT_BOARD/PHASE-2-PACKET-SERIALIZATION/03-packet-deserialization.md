# Story: Implement Packet Deserialization from Buffer

**Type:** Story  
**Phase:** 2 - Packet Serialization  
**Status:** Open  
**Priority:** High  
**Estimation:** 5 hours  
**Labels:** `test-first`, `protocol`, `serialization`, `phase-2`

## User Story

As a developer, I need to deserialize byte buffers into packet structures, so that received packets can be parsed and validated.

## Acceptance Criteria

- [ ] `test_packet_deserialize_basic` passes - deserializes simple packet correctly
- [ ] `test_packet_deserialize_with_payload` passes - deserializes packet with payload
- [ ] `test_packet_deserialize_validates_crc` passes - rejects packets with invalid CRC
- [ ] `test_packet_deserialize_validates_magic` passes - rejects packets with invalid magic byte
- [ ] `test_packet_deserialize_buffer_underrun` passes - handles incomplete buffers
- [ ] Tests run on native platform (`platformio test -e native`)
- [ ] Tests are in `test/test_protocol.cpp`

## Implementation Tasks

1. [ ] Add deserialization API to `firmware/lib/protocol/packet.h`:
   ```cpp
   // Deserialize byte buffer to packet
   // Returns number of bytes consumed, or -1 on error
   int packet_deserialize(packet_t* packet, const uint8_t* buffer, size_t buffer_size);
   
   // Validate packet after deserialization
   bool packet_validate(const packet_t* packet);
   ```

2. [ ] Implement deserialization in `firmware/lib/protocol/packet.c`:
   - Validate buffer size (minimum 5 bytes)
   - Check magic byte matches PACKET_MAGIC
   - Read header fields (magic, version, type, length)
   - Validate payload length doesn't exceed PACKET_MAX_PAYLOAD
   - Read payload bytes
   - Read CRC16 (big-endian)
   - Compute CRC and verify against received CRC
   - Return bytes consumed or -1 on error

3. [ ] Write deserialization tests in `test/test_protocol.cpp`:
   ```cpp
   void test_packet_deserialize_basic(void) {
       // Serialize a packet first
       packet_t original;
       original.magic = PACKET_MAGIC;
       original.version = PACKET_VERSION;
       original.type = PACKET_TYPE_COMMAND;
       original.length = 0;
       
       uint8_t buffer[PACKET_MAX_SIZE];
       int bytes = packet_serialize(&original, buffer, sizeof(buffer));
       TEST_ASSERT_GREATER_THAN(0, bytes);
       
       // Deserialize it back
       packet_t deserialized;
       int consumed = packet_deserialize(&deserialized, buffer, bytes);
       
       TEST_ASSERT_EQUAL(bytes, consumed);
       TEST_ASSERT_EQUAL_HEX8(PACKET_MAGIC, deserialized.magic);
       TEST_ASSERT_EQUAL_HEX8(PACKET_VERSION, deserialized.version);
       TEST_ASSERT_EQUAL_HEX8(PACKET_TYPE_COMMAND, deserialized.type);
       TEST_ASSERT_EQUAL(0, deserialized.length);
   }
   
   void test_packet_deserialize_with_payload(void) {
       packet_t original;
       original.magic = PACKET_MAGIC;
       original.version = PACKET_VERSION;
       original.type = PACKET_TYPE_TELEMETRY;
       original.length = 7;
       memcpy(original.payload, "TESTING", 7);
       
       uint8_t buffer[PACKET_MAX_SIZE];
       int bytes = packet_serialize(&original, buffer, sizeof(buffer));
       
       packet_t deserialized;
       int consumed = packet_deserialize(&deserialized, buffer, bytes);
       
       TEST_ASSERT_EQUAL(bytes, consumed);
       TEST_ASSERT_EQUAL(7, deserialized.length);
       TEST_ASSERT_EQUAL_MEMORY("TESTING", deserialized.payload, 7);
   }
   
   void test_packet_deserialize_validates_crc(void) {
       packet_t original;
       original.magic = PACKET_MAGIC;
       original.version = PACKET_VERSION;
       original.type = PACKET_TYPE_TELEMETRY;
       original.length = 3;
       memcpy(original.payload, "ABC", 3);
       
       uint8_t buffer[PACKET_MAX_SIZE];
       int bytes = packet_serialize(&original, buffer, sizeof(buffer));
       
       // Corrupt the CRC
       buffer[bytes - 1] ^= 0xFF;
       
       packet_t deserialized;
       int consumed = packet_deserialize(&deserialized, buffer, bytes);
       
       TEST_ASSERT_EQUAL(-1, consumed); // Should fail
   }
   
   void test_packet_deserialize_validates_magic(void) {
       uint8_t buffer[] = {0xBB, 0x01, 0x01, 0x00, 0x00, 0x00}; // Wrong magic
       
       packet_t packet;
       int consumed = packet_deserialize(&packet, buffer, sizeof(buffer));
       
       TEST_ASSERT_EQUAL(-1, consumed); // Should fail
   }
   
   void test_packet_deserialize_buffer_underrun(void) {
       uint8_t buffer[] = {0xAA, 0x01}; // Incomplete packet
       
       packet_t packet;
       int consumed = packet_deserialize(&packet, buffer, sizeof(buffer));
       
       TEST_ASSERT_EQUAL(-1, consumed); // Should fail
   }
   ```

4. [ ] Add test runner entries

5. [ ] Run tests: `platformio test -e native -f test_packet*`

6. [ ] Verify all tests pass

7. [ ] Verify firmware builds: `platformio run -e rpipico2w`

## Technical Notes

- **Deserialization Steps:**
  1. Validate minimum buffer size (5 bytes)
  2. Check magic byte == 0xAA
  3. Read header (version, type, length)
  4. Validate length ≤ 256
  5. Validate buffer has enough bytes for payload + CRC
  6. Read payload
  7. Read CRC16 (big-endian)
  8. Compute CRC and verify

- **Error Conditions:**
  - Buffer too small
  - Invalid magic byte
  - Payload length too large
  - CRC mismatch
  - Return -1 for any error

- **Success:**
  - Return total bytes consumed
  - Fill packet structure with parsed data

## Definition of Done

- [ ] Deserialization function implemented
- [ ] All validation tests pass
- [ ] CRC validation works correctly
- [ ] Magic byte validation works
- [ ] Buffer size checks work
- [ ] All tests pass on native platform
- [ ] Code compiles for target device (rpipico2w)
- [ ] No compiler warnings

## Related Issues

- Epic: #[EPIC-NUMBER] - TDD Roadmap
- Depends on: Story #[PREV] - Packet Serialization
- Blocks: Story #[NEXT] - Packet Buffer Management

## References

- File: `test/test_protocol.cpp`
- File: `firmware/lib/protocol/packet.h`
- File: `firmware/lib/protocol/packet.c`
