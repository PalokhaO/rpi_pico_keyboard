cmake_minimum_required(VERSION 3.13)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(test_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()
add_executable(test
  test.c
)
# pico_enable_stdio_usb(test 1)
pico_enable_stdio_uart(test 1)
pico_add_extra_outputs(test)
target_link_libraries(test
  pico_stdlib
  pico_cyw43_arch_none
)

#===================USB=====================

add_executable(dev_hid_composite)

target_sources(dev_hid_composite PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/main.c
  ${CMAKE_CURRENT_LIST_DIR}/usb_descriptors.c
)
# Make sure TinyUSB can find tusb_config.h
target_include_directories(dev_hid_composite PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

# In addition to pico_stdlib required for common PicoSDK functionality, add dependency on tinyusb_device
# for TinyUSB device support and tinyusb_board for the additional board support library used by the example
target_link_libraries(dev_hid_composite PUBLIC pico_stdlib tinyusb_device tinyusb_board)

# Uncomment this line to enable fix for Errata RP2040-E5 (the fix requires use of GPIO 15)
#target_compile_definitions(dev_hid_composite PUBLIC PICO_RP2040_USB_DEVICE_ENUMERATION_FIX=1)

pico_add_extra_outputs(dev_hid_composite)

#===================BLE======================
SET(TARGET_NAME "bt_keyboard")


# Adds common stuff for all the examples
add_library(bt_common INTERFACE)
target_compile_definitions(bt_common INTERFACE
        CYW43_LWIP=0
        PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS=3000
        #WANT_HCI_DUMP=1 # This enables btstack debug
        #ENABLE_SEGGER_RTT=1
        )
target_sources(bt_common INTERFACE
        bt_common.c
        )
target_link_libraries(bt_common INTERFACE
        pico_stdlib
        pico_btstack_ble
        pico_btstack_classic
        pico_btstack_cyw43
        pico_cyw43_arch_threadsafe_background
        )
target_include_directories(bt_common INTERFACE
        config # Use our own config
        )
suppress_btstack_warnings()


# Add an background example, pass btstack example name, target name, variant lib and extra libs
add_library(${TARGET_NAME}_lib INTERFACE)
target_sources(${TARGET_NAME}_lib INTERFACE
  # actual example
  hog_keyboard_demo.c
)
pico_btstack_make_gatt_header(${TARGET_NAME}_lib INTERFACE ${CMAKE_CURRENT_LIST_DIR}/hog_keyboard_demo.gatt)


add_executable(${TARGET_NAME})
target_link_libraries(${TARGET_NAME} PRIVATE
  ${TARGET_NAME}_lib
  bt_common
)
pico_enable_stdio_usb(${TARGET_NAME} 1)
pico_enable_stdio_uart(${TARGET_NAME} 0)
pico_add_extra_outputs(${TARGET_NAME})
