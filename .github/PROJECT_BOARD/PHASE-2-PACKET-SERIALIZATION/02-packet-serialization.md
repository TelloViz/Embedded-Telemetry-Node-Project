# Story: Implement Packet Serialization to Buffer

**Type:** Story  
**Phase:** 2 - Packet Serialization  
**Status:** Open  
**Priority:** High  
**Estimation:** 4 hours  
**Labels:** `test-first`, `protocol`, `serialization`, `phase-2`

## User Story

As a developer, I need to serialize packet structures into byte buffers, so that packets can be transmitted over serial/network interfaces.

## Acceptance Criteria

- [ ] `test_packet_serialize_basic` passes - serializes simple packet correctly
- [ ] `test_packet_serialize_with_payload` passes - serializes packet with payload data
- [ ] `test_packet_serialize_includes_crc` passes - verifies CRC is computed and appended
- [ ] `test_packet_serialize_buffer_size` passes - verifies buffer size validation
- [ ] Tests run on native platform (`platformio test -e native`)
- [ ] Tests are in `test/test_protocol.cpp`

## Implementation Tasks

1. [ ] Add serialization API to `firmware/lib/protocol/packet.h`:
   ```cpp
   // Serialize packet to byte buffer
   // Returns number of bytes written, or -1 on error
   int packet_serialize(const packet_t* packet, uint8_t* buffer, size_t buffer_size);
   
   // Get serialized size of packet (header + payload length + CRC)
   size_t packet_get_serialized_size(const packet_t* packet);
   ```

2. [ ] Implement serialization in `firmware/lib/protocol/packet.c`:
   - Validate input parameters
   - Check buffer size is sufficient
   - Write header fields (magic, version, type, length)
   - Write payload bytes (only up to length)
   - Compute and append CRC16 in big-endian format
   - Return bytes written

3. [ ] Write serialization tests in `test/test_protocol.cpp`:
   ```cpp
   void test_packet_serialize_basic(void) {
       packet_t packet;
       packet.magic = PACKET_MAGIC;
       packet.version = PACKET_VERSION;
       packet.type = PACKET_TYPE_TELEMETRY;
       packet.length = 0; // Empty payload
       
       uint8_t buffer[PACKET_MAX_SIZE];
       int bytes = packet_serialize(&packet, buffer, sizeof(buffer));
       
       TEST_ASSERT_EQUAL(5, bytes); // Magic + Ver + Type + Len + CRC(2)
       TEST_ASSERT_EQUAL_HEX8(PACKET_MAGIC, buffer[0]);
       TEST_ASSERT_EQUAL_HEX8(PACKET_VERSION, buffer[1]);
       TEST_ASSERT_EQUAL_HEX8(PACKET_TYPE_TELEMETRY, buffer[2]);
       TEST_ASSERT_EQUAL_HEX8(0, buffer[3]);
   }
   
   void test_packet_serialize_with_payload(void) {
       packet_t packet;
       packet.magic = PACKET_MAGIC;
       packet.version = PACKET_VERSION;
       packet.type = PACKET_TYPE_TELEMETRY;
       packet.length = 5;
       memcpy(packet.payload, "HELLO", 5);
       
       uint8_t buffer[PACKET_MAX_SIZE];
       int bytes = packet_serialize(&packet, buffer, sizeof(buffer));
       
       TEST_ASSERT_EQUAL(10, bytes); // 4 header + 5 payload + 2 CRC
       TEST_ASSERT_EQUAL_MEMORY("HELLO", &buffer[4], 5);
   }
   
   void test_packet_serialize_includes_crc(void) {
       packet_t packet;
       packet.magic = PACKET_MAGIC;
       packet.version = PACKET_VERSION;
       packet.type = PACKET_TYPE_TELEMETRY;
       packet.length = 3;
       memcpy(packet.payload, "ABC", 3);
       
       uint8_t buffer[PACKET_MAX_SIZE];
       int bytes = packet_serialize(&packet, buffer, sizeof(buffer));
       
       // CRC should be last 2 bytes (big-endian)
       uint16_t crc_received = (buffer[bytes-2] << 8) | buffer[bytes-1];
       
       // Recompute CRC on first (bytes-2) bytes
       uint16_t crc_computed = crc16_compute(buffer, bytes - 2);
       
       TEST_ASSERT_EQUAL_HEX16(crc_computed, crc_received);
   }
   
   void test_packet_serialize_buffer_size(void) {
       packet_t packet;
       packet.magic = PACKET_MAGIC;
       packet.length = 10;
       
       uint8_t small_buffer[5];
       int bytes = packet_serialize(&packet, small_buffer, 5);
       
       TEST_ASSERT_EQUAL(-1, bytes); // Should fail - buffer too small
   }
   ```

4. [ ] Add test runner entries

5. [ ] Run tests: `platformio test -e native -f test_packet_serialize*`

6. [ ] Verify all tests pass

7. [ ] Verify firmware builds: `platformio run -e rpipico2w`

## Technical Notes

- **Serialization Order:**
  1. Magic byte (1 byte)
  2. Version byte (1 byte)
  3. Type byte (1 byte)
  4. Length byte (1 byte)
  5. Payload (length bytes)
  6. CRC16 (2 bytes, big-endian)

- **CRC Computation:**
  - Include: all bytes except CRC field
  - Store: big-endian (MSB first)

- **Error Handling:**
  - Return -1 if buffer too small
  - Return -1 if packet or buffer is NULL
  - Return bytes written on success

## Definition of Done

- [ ] Serialization function implemented
- [ ] All validation tests pass
- [ ] CRC is correctly computed and appended
- [ ] Buffer size validation works
- [ ] All tests pass on native platform
- [ ] Code compiles for target device (rpipico2w)
- [ ] No compiler warnings

## Related Issues

- Epic: #[EPIC-NUMBER] - TDD Roadmap
- Depends on: Story #[PREV] - Packet Structure Definition
- Blocks: Story #[NEXT] - Packet Deserialization from Buffer

## References

- File: `test/test_protocol.cpp`
- File: `firmware/lib/protocol/packet.h`
- File: `firmware/lib/protocol/packet.c`
- File: `firmware/lib/protocol/crc16.h`
