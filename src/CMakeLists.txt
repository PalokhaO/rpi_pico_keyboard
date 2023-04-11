cmake_minimum_required(VERSION 3.13)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(test_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

SET(TARGET_NAME "keyboard")


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


add_executable(${TARGET_NAME})
pico_btstack_make_gatt_header(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/hog_keyboard_demo.gatt)
target_sources(${TARGET_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/usb.c
        ${CMAKE_CURRENT_LIST_DIR}/utils.c
        ${CMAKE_CURRENT_LIST_DIR}/config/usb_descriptors.c

        ${CMAKE_CURRENT_LIST_DIR}/bt.c
        ${CMAKE_CURRENT_LIST_DIR}/main.c
        ${CMAKE_CURRENT_LIST_DIR}/matrix.c
)
target_compile_definitions(${TARGET_NAME} PUBLIC
        CYW43_LWIP=0
        PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS=3000
        #WANT_HCI_DUMP=1 # This enables btstack debug
        #ENABLE_SEGGER_RTT=1
        )
target_include_directories(${TARGET_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/config
)
target_link_libraries(${TARGET_NAME} PUBLIC
        pico_stdlib
        bt_common
        tinyusb_device
        tinyusb_board
)

pico_enable_stdio_usb(${TARGET_NAME} 1)
pico_enable_stdio_uart(${TARGET_NAME} 0)

pico_add_extra_outputs(${TARGET_NAME})
