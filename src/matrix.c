
#include "matrix.h"

#include <pico/stdlib.h>
#include <stdio.h>
#include <pico/bootrom.h>

#define BOOTLOADER_SCANS 50000
static int first_row_scans = 0;

void matrix_init() {
    for (int i = 0; i < COLS; i++) {
        uint pin = col_pins[i];
        gpio_init(pin);
        gpio_set_dir(pin, true);
        gpio_put(pin, false);
    }
    for (int i = 0; i < ROWS; i++) {
        uint pin = row_pins[i];
        gpio_init(pin);
        gpio_set_dir(pin, false);
        gpio_pull_down(pin);
    }
}

void matrix_scan() {
    bool left_row_pressed = true;
    for (int j = 0; j < COLS; j++) {
        uint col_pin = col_pins[j];
        gpio_put(col_pin, true);

        for (int i = 0; i < ROWS; i++) {
            uint row_pin = row_pins[i];
            bool pressed = gpio_get(row_pins[i]);
            if (!j && !pressed) {
                left_row_pressed = false;
            }
            matrix_state[i][j] = pressed;
        }
        gpio_put(col_pin, false);
        sleep_us(5);
    }
    first_row_scans = matrix_state[0][0]
        ? first_row_scans + 1
        : 0;
    if (first_row_scans >= BOOTLOADER_SCANS) {
        reset_usb_boot(0, 0);
    }
}
