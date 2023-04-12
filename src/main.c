
#include "bt.h"
#include "usb.h"
#include "matrix.h"

#include <pico/stdlib.h>
#include <pico/stdio.h>
#include <tusb.h>
#include "pico/cyw43_arch.h"
#include "utils.h"
#include "leds.h"

#include "bt_common.h"

const int interval = 10;
uint16_t leds_status = 0;

void heartbeat() {
    EVERY_MS(5000);
    printf(".\n");
}

void matrix() {
    EVERY_US(5);

    matrix_scan();
}

void leds() {
    EVERY_MS(1000);
    leds_status <<= 1;
    leds_status = leds_status
        ? leds_status
        : 1;
    leds_write(leds_status);
}

int main() {
    leds_init();
    leds_write(leds_status);
    leds_enable(true);

    tusb_init();
    stdio_init_all();
    stdio_set_driver_enabled(&stdio_usb, true);

    matrix_init();

    int res = picow_bt_example_init();
    if (res) {
        return -1;
    }
    btstack_main();

    while (1) {
        tud_task();

        heartbeat();

        hid_task_usb(interval);
        hid_task_bt(interval);

        matrix();
        leds();
    }
}
