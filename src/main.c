
#include "bt.h"
#include "usb.h"

#include <pico/stdlib.h>
#include <pico/stdio.h>
#include <tusb.h>
#include "pico/cyw43_arch.h"
#include "utils.h"

#include "bt_common.h"

const int interval = 10;

void heartbeat() {
    EVERY(5000);
    printf(".\n");
}


void tud() {
    // EVERY(11)

    tud_task(); // tinyusb device task
}

int main() {
    tusb_init();
    stdio_init_all();
    stdio_set_driver_enabled(&stdio_usb, true);

    int res = picow_bt_example_init();
    if (res) {
        return -1;
    }
    btstack_main();

    while (1) {
        tud();

        heartbeat();

        hid_task_usb(interval);
        hid_task_bt(interval);
    }
}
