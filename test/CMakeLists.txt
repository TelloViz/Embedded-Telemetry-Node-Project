cmake_minimum_required(VERSION 3.10)
project(EmbeddedTelemetryNodeTests)

# Include directories for source and lib
include_directories(../firmware/src)
include_directories(../firmware/lib)

# Add test executable
add_executable(test_app test_app.cpp)
    ../firmware/src/app.cpp
    ../firmware/src/hal/led/hal_led.cpp
    ../firmware/src/hal/time/hal_time.cpp
    ../firmware/src/hal/serial/serial_io.cpp
    unity/src/unity.c


enable_testing()
add_test(NAME AppTests COMMAND test_app)