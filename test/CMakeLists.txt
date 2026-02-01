cmake_minimum_required(VERSION 3.10)
project(EmbeddedTelemetryNodeTests C CXX)

# Set compile definitions for unit testing
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DUNIT_TEST")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUNIT_TEST")

# Find Unity framework
find_package(Unity REQUIRED)

# Include directories 
include_directories(../firmware/src)
include_directories(../firmware/lib)
include_directories(../firmware/lib/protocol)

# Protocol library source files
set(PROTOCOL_SOURCES
    ../firmware/lib/protocol/packet.c
    ../firmware/lib/protocol/parser.c
    ../firmware/lib/protocol/crc16.c
)

# App source files
set(APP_SOURCES
    app_impl.cpp
)

# Test executable - test_app
add_executable(test_app 
    test_app.cpp
    ${APP_SOURCES}
    ${PROTOCOL_SOURCES}
)
target_link_libraries(test_app PRIVATE Unity::Unity)
target_include_directories(test_app PRIVATE ../firmware/lib/protocol)

# Test executable - test_protocol
add_executable(test_protocol
    test_protocol.cpp
    ${PROTOCOL_SOURCES}
)
target_link_libraries(test_protocol PRIVATE Unity::Unity)

enable_testing()
add_test(NAME test_app COMMAND test_app)
add_test(NAME test_protocol COMMAND test_protocol)