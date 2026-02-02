# Story: Integrate CRC16 with Packet Structure

**Type:** Story  
**Phase:** 1 - Protocol Layer (CRC16)  
**Status:** Open  
**Priority:** High  
**Estimation:** 4 hours  
**Labels:** `test-first`, `protocol`, `crc16`, `phase-1`, `integration`

## User Story

As a developer, I need to integrate CRC16 computation with the packet structure, so that every packet can be validated for integrity when received.

## Acceptance Criteria

- [ ] `test_packet_crc_append` passes - verifies CRC is correctly appended to packet
- [ ] `test_packet_crc_verify_valid` passes - verifies valid packet passes CRC check
- [ ] `test_packet_crc_verify_corrupted` passes - verifies corrupted packet fails CRC check
- [ ] Tests run on native platform (`platformio test -e native`)
- [ ] Tests are in `test/test_protocol.cpp`

## Implementation Tasks

1. [ ] Define packet structure in `firmware/lib/protocol/packet.h`:
   ```cpp
   #ifndef PACKET_H
   #define PACKET_H
   
   #include <stdint.h>
   #include <stddef.h>
   #include "crc16.h"
   
   #define PACKET_MAX_PAYLOAD 256
   
   typedef struct {
       uint8_t header;           // Packet type/command
       uint8_t length;           // Payload length
       uint8_t payload[PACKET_MAX_PAYLOAD];
       uint16_t crc;             // CRC16 checksum (last 2 bytes)
   } packet_t;
   
   // Compute CRC for packet (header + length + payload)
   uint16_t packet_compute_crc(const packet_t* packet);
   
   // Verify packet CRC matches computed value
   bool packet_verify_crc(const packet_t* packet);
   
   #endif
   ```

2. [ ] Implement packet CRC functions in `firmware/lib/protocol/packet.c`

3. [ ] Write integration tests in `test/test_protocol.cpp`:
   ```cpp
   void test_packet_crc_append(void) {
       packet_t packet;
       packet.header = 0x01;
       packet.length = 5;
       memcpy(packet.payload, "HELLO", 5);
       
       packet.crc = packet_compute_crc(&packet);
       
       TEST_ASSERT_NOT_EQUAL(0x0000, packet.crc);
       TEST_ASSERT_NOT_EQUAL(0xFFFF, packet.crc);
   }
   
   void test_packet_crc_verify_valid(void) {
       packet_t packet;
       packet.header = 0x01;
       packet.length = 5;
       memcpy(packet.payload, "HELLO", 5);
       packet.crc = packet_compute_crc(&packet);
       
       bool valid = packet_verify_crc(&packet);
       TEST_ASSERT_TRUE(valid);
   }
   
   void test_packet_crc_verify_corrupted(void) {
       packet_t packet;
       packet.header = 0x01;
       packet.length = 5;
       memcpy(packet.payload, "HELLO", 5);
       packet.crc = packet_compute_crc(&packet);
       
       // Corrupt the payload
       packet.payload[0] = 'X';
       
       bool valid = packet_verify_crc(&packet);
       TEST_ASSERT_FALSE(valid);
   }
   ```

4. [ ] Add test runner entries

5. [ ] Run all protocol tests: `platformio test -e native -f test_protocol*`

6. [ ] Verify all tests pass

7. [ ] Verify firmware builds: `platformio run -e rpipico2w`

## Technical Notes

- **Packet Structure:**
  - Header (1 byte): packet type/command
  - Length (1 byte): payload length (0-255)
  - Payload (up to 256 bytes): data
  - CRC (2 bytes): checksum of header + length + payload

- **CRC Computation:**
  - Include: header, length, and payload bytes
  - Exclude: CRC field itself
  - Use incremental CRC for efficiency

- **CRC Verification:**
  - Recompute CRC and compare with packet's CRC field
  - Return true if match, false if mismatch

## Definition of Done

- [ ] Packet structure defined with CRC field
- [ ] CRC computation function implemented
- [ ] CRC verification function implemented
- [ ] All integration tests pass
- [ ] Tests verify valid and corrupted packets
- [ ] All tests pass on native platform
- [ ] Code compiles for target device (rpipico2w)
- [ ] No compiler warnings

## Related Issues

- Epic: #[EPIC-NUMBER] - TDD Roadmap
- Depends on: Story #[PREV] - CRC16 Incremental Computation
- Blocks: Phase 2 - Packet Serialization

## References

- File: `test/test_protocol.cpp`
- File: `firmware/lib/protocol/packet.h`
- File: `firmware/lib/protocol/packet.c`
- File: `firmware/lib/protocol/crc16.h`
- Docs: [TESTING.md](../../docs/TESTING.md)

## Notes

This story completes Phase 1 (CRC16 Implementation) and sets up the foundation for Phase 2 (Packet Serialization). After this story is complete:
- CRC16 library is fully tested and functional
- Basic packet structure is defined
- Ready to implement serialization/deserialization in Phase 2
