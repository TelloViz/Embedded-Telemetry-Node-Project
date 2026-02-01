```bash
# Native unit tests
platformio test -e native

# Device build (requires Pico 2W)
platformio run - rpipico2w
platformio run - rpipico2w --target upload
```

---

## Future: Test Framework Migration Path

As the project matures and complexity grows, the following is being considered:

** GoogleTest (C++ Standard)**
- Industry standard
- Better IDE integration
- Richer assertion library
- Largeer test ecosystem

** Migration feasibility**:
- Keep existing test structure
- Gradual migration of test cases
- Both frameworks can coexist during transition

---

## Metrics to Track

- **Code Coverage**: Aim for 80%+ line coverage
- **Test Pass Rate**: 100% expected
- **Test Execution Time**: Keep native tests <5 secionds
- **Defect Detection Rate**: Track bugs caught by each test tier

---

## Notes for Contributors

1. **New features** -- Write tests first (TDD Approach)
2. **Bug fixes** -- Add regression test before fix
3. **HAL changes** -- Update both unit test mocks and integration tests
4. **Device changes** -- Add corresponding device integration test

Every code change should have a test that validates its behavior.