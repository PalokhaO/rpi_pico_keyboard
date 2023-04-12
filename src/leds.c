#include "leds.h"

#include <pico/stdlib.h>
#include <stdio.h>
#include <hardware/gpio.h>

void leds_init() {
    gpio_init(SER_PIN);
    gpio_set_dir(SER_PIN, true);
    gpio_put(SER_PIN, false);

    gpio_init(OE_PIN);
    gpio_set_dir(OE_PIN, true);
    gpio_put(OE_PIN, true);

    gpio_init(RCLK_PIN);
    gpio_set_dir(RCLK_PIN, true);
    gpio_put(RCLK_PIN, false);

    gpio_init(SRCLK_PIN);
    gpio_set_dir(SRCLK_PIN, true);
    gpio_put(SRCLK_PIN, false);
}

void leds_enable(bool enabled) {
    gpio_put(OE_PIN, !enabled);
}

void leds_write(uint16_t mask) {
    // Revert the pin value for index 0 (CAPS)
    mask ^= 1;
    printf("Before loop: %x\n", mask);
    for (uint16_t pin_mask = 1; pin_mask > 0; pin_mask <<= 1) {
        printf("pin_mask: %x\n", pin_mask);
        gpio_put(SER_PIN, mask & pin_mask);
        sleep_us(1);
        gpio_put(SRCLK_PIN, true);
        sleep_us(1);
        gpio_put(SRCLK_PIN, false);
    }
    sleep_us(1);
    gpio_put(RCLK_PIN, true);
    sleep_us(1);
    gpio_put(RCLK_PIN, false);
}
