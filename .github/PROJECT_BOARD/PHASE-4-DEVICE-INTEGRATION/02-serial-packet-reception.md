# Story: Device Integration - Serial Packet Reception

**Type:** Story  
**Phase:** 4 - Device Integration Tests  
**Status:** Open  
**Priority:** High  
**Estimation:** 4 hours  
**Labels:** `device-test`, `integration`, `serial`, `phase-4`

## User Story

As a developer, I need to test packet reception and parsing on actual hardware, so that I can verify command handling works end-to-end.

## Acceptance Criteria

- [ ] Test packet deserialization from serial on Pico 2W hardware
- [ ] Verify CRC validation works on device
- [ ] Verify command parsing and dispatch works
- [ ] Test can be run with: `platformio test -e rpipico2w`

## Implementation Tasks

1. [ ] Write device test for packet reception
2. [ ] Test CRC validation on hardware
3. [ ] Test command parsing on hardware
4. [ ] Run tests on actual Pico 2W
5. [ ] Document test procedure

**Estimation:** 4 hours
