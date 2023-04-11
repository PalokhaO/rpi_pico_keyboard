
#include "matrix.h"

#include <pico/stdlib.h>
#include <stdio.h>
#include <hardware/gpio.h>

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
    printf("Matrix_scan: ");
    
    for (int j = 0; j < COLS; j++) {
        uint col_pin = col_pins[j];
        gpio_put(col_pin, true);

        for (int i = 0; i < ROWS; i++) {
            uint row_pin = row_pins[i];
            bool pressed = gpio_get(row_pins[i]);
            if (pressed) {
                printf("%dx%d, ", i, j);
            }
            matrix_state[i][j] = pressed;
        }
        gpio_put(col_pin, false);
        sleep_us(5);
    }
    printf("\n");
}
