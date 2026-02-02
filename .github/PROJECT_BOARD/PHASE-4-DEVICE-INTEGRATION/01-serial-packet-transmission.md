# Story: Device Integration - Serial Packet Transmission

**Type:** Story  
**Phase:** 4 - Device Integration Tests  
**Status:** Open  
**Priority:** High  
**Estimation:** 4 hours  
**Labels:** `device-test`, `integration`, `serial`, `phase-4`

## User Story

As a developer, I need to test packet transmission over serial on actual hardware, so that I can verify the protocol stack works end-to-end.

## Acceptance Criteria

- [ ] Test packet serialization and transmission on Pico 2W hardware
- [ ] Verify CRC is computed correctly on device
- [ ] Verify packet format matches specification
- [ ] Test can be run with: `platformio test -e rpipico2w`
- [ ] Test is in `test/test_device_integration.cpp`

## Implementation Tasks

1. [ ] Create `test/test_device_integration.cpp`
2. [ ] Write device test for packet transmission
3. [ ] Configure PlatformIO for device testing
4. [ ] Run test on actual Pico 2W hardware
5. [ ] Document test procedure

**Estimation:** 4 hours
**Requirements:** Raspberry Pi Pico 2W hardware, USB cable, serial monitor
