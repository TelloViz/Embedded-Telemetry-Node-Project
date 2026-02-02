# Story: Define Packet Structure and Constants

**Type:** Story  
**Phase:** 2 - Packet Serialization  
**Status:** Open  
**Priority:** High  
**Estimation:** 2 hours  
**Labels:** `test-first`, `protocol`, `serialization`, `phase-2`

## User Story

As a developer, I need to define a complete binary packet structure with header, payload, and footer fields, so that telemetry data can be transmitted reliably over serial/network interfaces.

## Acceptance Criteria

- [ ] `test_packet_structure_size` passes - verifies packet structure has expected memory layout
- [ ] `test_packet_header_magic` passes - verifies magic byte identifies packet type
- [ ] `test_packet_max_size` passes - verifies packet size constraints
- [ ] Tests run on native platform (`platformio test -e native`)
- [ ] Tests are in `test/test_protocol.cpp`

## Implementation Tasks

1. [ ] Define complete packet structure in `firmware/lib/protocol/packet.h`:
   ```cpp
   #define PACKET_MAGIC 0xAA           // Packet start marker
   #define PACKET_VERSION 0x01         // Protocol version
   #define PACKET_MAX_PAYLOAD 256      // Maximum payload bytes
   #define PACKET_MIN_SIZE 5           // Magic + Ver + Len + CRC (2 bytes)
   #define PACKET_MAX_SIZE (PACKET_MIN_SIZE + PACKET_MAX_PAYLOAD)
   
   typedef enum {
       PACKET_TYPE_TELEMETRY = 0x01,
       PACKET_TYPE_COMMAND = 0x02,
       PACKET_TYPE_RESPONSE = 0x03,
       PACKET_TYPE_ERROR = 0x04
   } packet_type_t;
   
   typedef struct __attribute__((packed)) {
       uint8_t magic;                  // Always PACKET_MAGIC (0xAA)
       uint8_t version;                // Protocol version
       uint8_t type;                   // Packet type (packet_type_t)
       uint8_t length;                 // Payload length (0-256)
       uint8_t payload[PACKET_MAX_PAYLOAD];
       uint16_t crc;                   // CRC16 checksum (big-endian)
   } packet_t;
   ```

2. [ ] Write structure validation tests in `test/test_protocol.cpp`:
   ```cpp
   void test_packet_structure_size(void) {
       // Verify packed structure size
       size_t expected = 1 + 1 + 1 + 1 + 256 + 2; // 262 bytes
       TEST_ASSERT_EQUAL(expected, sizeof(packet_t));
   }
   
   void test_packet_header_magic(void) {
       packet_t packet;
       packet.magic = PACKET_MAGIC;
       TEST_ASSERT_EQUAL_HEX8(0xAA, packet.magic);
   }
   
   void test_packet_max_size(void) {
       TEST_ASSERT_EQUAL(5, PACKET_MIN_SIZE);
       TEST_ASSERT_EQUAL(256, PACKET_MAX_PAYLOAD);
       TEST_ASSERT_EQUAL(261, PACKET_MAX_SIZE);
   }
   ```

3. [ ] Add test runner entries

4. [ ] Run tests: `platformio test -e native -f test_packet*`

5. [ ] Verify tests pass

6. [ ] Verify firmware builds: `platformio run -e rpipico2w`

## Technical Notes

- **Packet Structure:**
  - Magic byte (0xAA): identifies start of packet
  - Version byte: protocol version for future compatibility
  - Type byte: identifies packet purpose (telemetry/command/response/error)
  - Length byte: payload size (0-256)
  - Payload: variable-length data
  - CRC16: checksum in big-endian format

- **Packed Structure:**
  - Use `__attribute__((packed))` to prevent padding
  - Ensures consistent binary layout across platforms
  - Critical for wire protocol compatibility

- **Design Decisions:**
  - 256-byte max payload supports most use cases
  - Total packet size ≤ 261 bytes fits in embedded buffers
  - Magic byte enables frame synchronization

## Definition of Done

- [ ] Packet structure defined with all fields
- [ ] Packet type enum defined
- [ ] Constants defined for sizes and limits
- [ ] Structure validation tests pass
- [ ] All tests pass on native platform
- [ ] Code compiles for target device (rpipico2w)
- [ ] No compiler warnings

## Related Issues

- Epic: #[EPIC-NUMBER] - TDD Roadmap
- Depends on: Phase 1 - CRC16 Integration
- Blocks: Story #[NEXT] - Packet Serialization to Buffer

## References

- File: `test/test_protocol.cpp`
- File: `firmware/lib/protocol/packet.h`
- Docs: [TESTING.md](../../docs/TESTING.md)
