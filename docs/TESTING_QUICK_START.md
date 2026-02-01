# Quick Reference: Running Tests

## Native Unit Tests (Recommended for Development)
```bash
platformio test -e native
```
- No hardware required
- Runs in < 3 seconds
- Tests app logic with mocked HAL layer

## Native Tests with Verbose Output
```bash
platformio test -e native -vvv
```

## Device Build & Upload
```bash
# Build only
platformio run -e rpipico2w

# Build and upload
platformio run -e rpipico2w --target upload

# Monitor serial output
platformio device monitor --port COM3 --baud 115200
```

## Development Workflow

1. **Make code changes** in `firmware/src/app.cpp`
2. **Update test copy** if app logic changes:
   ```bash
   copy firmware\src\app.cpp test\app_impl.cpp  # Windows
   cp firmware/src/app.cpp test/app_impl.cpp    # Linux/Mac
   ```
3. **Run tests** to validate: `platformio test -e native`
4. **Build for device** when ready: `platformio run -e rpipico2w`

## Test Architecture
- **Unit tests**: Mock all HAL layers, test app logic in isolation
- **Mocks**: `MockHalLed`, `MockHalTime`, `MockHalSerial`, `MockLogger`
- **Framework**: Unity (lightweight, zero dependencies)

For detailed testing strategy and roadmap, see [docs/TESTING.md](docs/TESTING.md)
