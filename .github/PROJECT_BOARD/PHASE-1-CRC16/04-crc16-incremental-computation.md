# Story: Implement CRC16 Incremental Computation

**Type:** Story  
**Phase:** 1 - Protocol Layer (CRC16)  
**Status:** Open  
**Priority:** Medium  
**Estimation:** 3 hours  
**Labels:** `test-first`, `protocol`, `crc16`, `phase-1`, `optimization`

## User Story

As a developer, I need to compute CRC16 incrementally over multiple data chunks, so that I can calculate checksums for streaming data or large buffers without holding everything in memory.

## Acceptance Criteria

- [ ] `test_crc16_incremental_matches_single_pass` passes - verifies incremental CRC matches single-pass CRC
- [ ] `test_crc16_incremental_multiple_chunks` passes - verifies CRC over 3+ chunks
- [ ] Tests run on native platform (`platformio test -e native`)
- [ ] Tests are in `test/test_protocol.cpp`

## Implementation Tasks

1. [ ] Update `firmware/lib/protocol/crc16.h` with incremental API:
   ```cpp
   // Compute CRC from scratch
   uint16_t crc16_compute(const uint8_t* data, size_t length);
   
   // Update existing CRC with new data (for incremental computation)
   uint16_t crc16_update(uint16_t crc, const uint8_t* data, size_t length);
   
   // Initialize CRC for incremental computation
   #define CRC16_INIT 0xFFFF
   ```

2. [ ] Implement `crc16_update()` in `firmware/lib/protocol/crc16.c`

3. [ ] Refactor `crc16_compute()` to use `crc16_update()` internally

4. [ ] Write unit tests in `test/test_protocol.cpp`:
   ```cpp
   void test_crc16_incremental_matches_single_pass(void) {
       const uint8_t data[] = "123456789";
       
       // Single pass
       uint16_t crc_single = crc16_compute(data, 9);
       
       // Incremental (3 chunks: "123", "456", "789")
       uint16_t crc_incr = CRC16_INIT;
       crc_incr = crc16_update(crc_incr, data, 3);     // "123"
       crc_incr = crc16_update(crc_incr, data + 3, 3); // "456"
       crc_incr = crc16_update(crc_incr, data + 6, 3); // "789"
       
       TEST_ASSERT_EQUAL_HEX16(crc_single, crc_incr);
   }
   
   void test_crc16_incremental_multiple_chunks(void) {
       uint16_t crc = CRC16_INIT;
       const uint8_t chunk1[] = "Hello";
       const uint8_t chunk2[] = ", ";
       const uint8_t chunk3[] = "World!";
       
       crc = crc16_update(crc, chunk1, 5);
       crc = crc16_update(crc, chunk2, 2);
       crc = crc16_update(crc, chunk3, 6);
       
       // Should match single-pass CRC of "Hello, World!"
       const uint8_t full[] = "Hello, World!";
       uint16_t crc_expected = crc16_compute(full, 13);
       
       TEST_ASSERT_EQUAL_HEX16(crc_expected, crc);
   }
   ```

5. [ ] Add test runner entries

6. [ ] Run tests: `platformio test -e native -f test_crc16*`

7. [ ] Verify all tests pass

8. [ ] Verify firmware builds: `platformio run -e rpipico2w`

## Technical Notes

- **Incremental Computation:**
  - Allows CRC calculation over multiple calls
  - Useful for streaming data (serial, network)
  - Reduces memory footprint for large packets

- **API Design:**
  - `crc16_compute()` - convenience function for single-pass
  - `crc16_update()` - core function for incremental computation
  - `CRC16_INIT` - initial value constant

- **Implementation:**
  - `crc16_compute()` can simply call `crc16_update()` with `CRC16_INIT`
  - Maintains same algorithm and lookup table

## Definition of Done

- [ ] Incremental API implemented and tested
- [ ] Tests verify incremental matches single-pass
- [ ] Tests verify multiple chunk scenarios
- [ ] All tests pass on native platform
- [ ] Code compiles for target device (rpipico2w)
- [ ] No compiler warnings
- [ ] API documented in header file

## Related Issues

- Epic: #[EPIC-NUMBER] - TDD Roadmap
- Depends on: Story #[PREV] - CRC16 Edge Cases Test
- Blocks: Story #[NEXT] - CRC16 Integration with Packet Structure

## References

- File: `test/test_protocol.cpp`
- File: `firmware/lib/protocol/crc16.h`
- File: `firmware/lib/protocol/crc16.c`
- Docs: [TESTING_QUICK_START.md](../../docs/TESTING_QUICK_START.md)
