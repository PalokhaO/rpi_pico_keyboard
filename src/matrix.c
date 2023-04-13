
#include "matrix.h"

#include <pico/stdlib.h>
#include <stdio.h>
#include <pico/bootrom.h>

#define BOOTLOADER_CYCLES 50000
static int bootloader_cycles = 0;

void matrix_init() {
    for (int i = 0; i < MATRIX_COLS; i++) {
        uint pin = col_pins[i];
        gpio_init(pin);
        gpio_set_dir(pin, true);
        gpio_set_input_enabled(pin, true);
        gpio_put(pin, false);
    }
    for (int i = 0; i < MATRIX_ROWS; i++) {
        uint pin = row_pins[i];
        gpio_init(pin);
        gpio_set_dir(pin, false);
        gpio_pull_down(pin);
    }
}

void matrix_scan() {
    bool left_row_pressed = true;
    for (int j = 0; j < MATRIX_COLS; j++) {
        uint col_pin = col_pins[j];
        gpio_put(col_pin, true);
        sleep_us(5);

        for (int i = 0; i < MATRIX_ROWS; i++) {
            uint row_pin = row_pins[i];
            bool pressed = gpio_get(row_pins[i]);
            if (!j && !pressed) {
                left_row_pressed = false;
            }
            matrix_state[i][j] = pressed;
            if (pressed) {
                // printf("In scan: %dx%d\n", i, j);
            }
        }
        gpio_put(col_pin, false);
    }
    bootloader_cycles = matrix_state[0][0]
        ? bootloader_cycles + 1
        : 0;
    if (bootloader_cycles >= BOOTLOADER_CYCLES) {
        reset_usb_boot(0, 0);
    }
}
