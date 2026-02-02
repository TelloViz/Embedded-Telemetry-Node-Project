# Story: Implement Packet Buffer Management

**Type:** Story  
**Phase:** 2 - Packet Serialization  
**Status:** Open  
**Priority:** Medium  
**Estimation:** 4 hours  
**Labels:** `test-first`, `protocol`, `serialization`, `phase-2`, `buffer-management`

## User Story

As a developer, I need efficient buffer management for packet operations, so that I can minimize memory copies and support streaming data.

## Acceptance Criteria

- [ ] `test_packet_builder_init` passes - initializes packet builder correctly
- [ ] `test_packet_builder_append` passes - appends payload data incrementally
- [ ] `test_packet_builder_finalize` passes - computes CRC and finalizes packet
- [ ] `test_packet_builder_overflow` passes - handles buffer overflow
- [ ] Tests run on native platform (`platformio test -e native`)
- [ ] Tests are in `test/test_protocol.cpp`

## Implementation Tasks

1. [ ] Add packet builder API to `firmware/lib/protocol/packet.h`:
   ```cpp
   // Packet builder for incremental construction
   typedef struct {
       packet_t* packet;
       size_t payload_written;
       bool finalized;
   } packet_builder_t;
   
   // Initialize packet builder
   void packet_builder_init(packet_builder_t* builder, packet_t* packet, 
                            uint8_t type);
   
   // Append data to payload (returns bytes appended, 0 if full)
   size_t packet_builder_append(packet_builder_t* builder, 
                                 const uint8_t* data, size_t length);
   
   // Finalize packet (compute CRC, set length)
   bool packet_builder_finalize(packet_builder_t* builder);
   
   // Get current payload size
   size_t packet_builder_get_size(const packet_builder_t* builder);
   ```

2. [ ] Implement packet builder in `firmware/lib/protocol/packet.c`

3. [ ] Write buffer management tests in `test/test_protocol.cpp`:
   ```cpp
   void test_packet_builder_init(void) {
       packet_t packet;
       packet_builder_t builder;
       
       packet_builder_init(&builder, &packet, PACKET_TYPE_TELEMETRY);
       
       TEST_ASSERT_EQUAL_PTR(&packet, builder.packet);
       TEST_ASSERT_EQUAL(0, builder.payload_written);
       TEST_ASSERT_FALSE(builder.finalized);
       TEST_ASSERT_EQUAL_HEX8(PACKET_MAGIC, packet.magic);
       TEST_ASSERT_EQUAL_HEX8(PACKET_VERSION, packet.version);
       TEST_ASSERT_EQUAL_HEX8(PACKET_TYPE_TELEMETRY, packet.type);
   }
   
   void test_packet_builder_append(void) {
       packet_t packet;
       packet_builder_t builder;
       packet_builder_init(&builder, &packet, PACKET_TYPE_COMMAND);
       
       const uint8_t data1[] = "Hello ";
       const uint8_t data2[] = "World!";
       
       size_t written1 = packet_builder_append(&builder, data1, 6);
       size_t written2 = packet_builder_append(&builder, data2, 6);
       
       TEST_ASSERT_EQUAL(6, written1);
       TEST_ASSERT_EQUAL(6, written2);
       TEST_ASSERT_EQUAL(12, packet_builder_get_size(&builder));
       TEST_ASSERT_EQUAL_MEMORY("Hello World!", packet.payload, 12);
   }
   
   void test_packet_builder_finalize(void) {
       packet_t packet;
       packet_builder_t builder;
       packet_builder_init(&builder, &packet, PACKET_TYPE_TELEMETRY);
       
       const uint8_t data[] = "TEST";
       packet_builder_append(&builder, data, 4);
       
       bool success = packet_builder_finalize(&builder);
       
       TEST_ASSERT_TRUE(success);
       TEST_ASSERT_TRUE(builder.finalized);
       TEST_ASSERT_EQUAL(4, packet.length);
       TEST_ASSERT_NOT_EQUAL(0x0000, packet.crc);
       TEST_ASSERT_NOT_EQUAL(0xFFFF, packet.crc);
   }
   
   void test_packet_builder_overflow(void) {
       packet_t packet;
       packet_builder_t builder;
       packet_builder_init(&builder, &packet, PACKET_TYPE_TELEMETRY);
       
       // Try to write more than PACKET_MAX_PAYLOAD
       uint8_t large_data[300];
       memset(large_data, 0xAA, sizeof(large_data));
       
       size_t written = packet_builder_append(&builder, large_data, 300);
       
       TEST_ASSERT_EQUAL(PACKET_MAX_PAYLOAD, written); // Should cap at max
       TEST_ASSERT_EQUAL(PACKET_MAX_PAYLOAD, packet_builder_get_size(&builder));
   }
   ```

4. [ ] Add test runner entries

5. [ ] Run tests: `platformio test -e native -f test_packet_builder*`

6. [ ] Verify all tests pass

7. [ ] Verify firmware builds: `platformio run -e rpipico2w`

## Technical Notes

- **Packet Builder Benefits:**
  - Incremental payload construction
  - No intermediate buffers needed
  - Automatic CRC computation on finalize
  - Overflow protection

- **Usage Pattern:**
  ```cpp
  packet_t packet;
  packet_builder_t builder;
  
  packet_builder_init(&builder, &packet, PACKET_TYPE_TELEMETRY);
  packet_builder_append(&builder, sensor_data, sizeof(sensor_data));
  packet_builder_append(&builder, timestamp, sizeof(timestamp));
  packet_builder_finalize(&builder);
  
  // packet is now ready to serialize and transmit
  ```

- **Implementation Notes:**
  - Track payload_written to prevent overflow
  - Finalize sets length field and computes CRC
  - Once finalized, no more appends allowed

## Definition of Done

- [ ] Packet builder API implemented
- [ ] All buffer management tests pass
- [ ] Overflow protection works correctly
- [ ] Incremental append works
- [ ] Finalization computes CRC correctly
- [ ] All tests pass on native platform
- [ ] Code compiles for target device (rpipico2w)
- [ ] No compiler warnings

## Related Issues

- Epic: #[EPIC-NUMBER] - TDD Roadmap
- Depends on: Story #[PREV] - Packet Deserialization
- Blocks: Story #[NEXT] - Endianness Handling

## References

- File: `test/test_protocol.cpp`
- File: `firmware/lib/protocol/packet.h`
- File: `firmware/lib/protocol/packet.c`
