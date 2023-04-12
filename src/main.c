
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
// Just color everything teal for now
uint16_t leds_status = 0b0011011011011011;

void heartbeat() {
    EVERY_MS(5000);
    printf(".\n");
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

        matrix_scan();
    }
}
