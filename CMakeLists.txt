# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
include(${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico-test C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()


# Set flags and directory variables
set(FREERTOS_CFG_DIRECTORY "${CMAKE_SOURCE_DIR}/FreeRTOS-Config")
set(FREERTOS_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/FreeRTOS-Kernel")

# Add FreeRTOS as a library
add_library(FreeRTOS STATIC
  ${FREERTOS_SRC_DIRECTORY}/event_groups.c
  ${FREERTOS_SRC_DIRECTORY}/list.c
  ${FREERTOS_SRC_DIRECTORY}/queue.c
  ${FREERTOS_SRC_DIRECTORY}/stream_buffer.c
  ${FREERTOS_SRC_DIRECTORY}/tasks.c
  ${FREERTOS_SRC_DIRECTORY}/timers.c
  ${FREERTOS_SRC_DIRECTORY}/portable/MemMang/heap_3.c
  ${FREERTOS_SRC_DIRECTORY}/portable/GCC/ARM_CM0/port.c
)

# Build FreeRTOS
target_include_directories(FreeRTOS PUBLIC
  ${FREERTOS_CFG_DIRECTORY}/
  ${FREERTOS_SRC_DIRECTORY}/include
  ${FREERTOS_SRC_DIRECTORY}/portable/GCC/ARM_CM0
)

# Add executable. Default name is the project name, version 0.1
add_executable(pico-test pico-test.c )

pico_set_program_name(pico-test "pico-test")
pico_set_program_version(pico-test "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(pico-test 1)
pico_enable_stdio_usb(pico-test 0)

# Add the standard library to the build
target_link_libraries(pico-test
  # RP2040
  PRIVATE pico_stdlib
  PRIVATE hardware_spi
  # FreeRTOS
  PRIVATE FreeRTOS
)

# Add the standard include files to the build
target_include_directories(pico-test PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

pico_add_extra_outputs(pico-test)
