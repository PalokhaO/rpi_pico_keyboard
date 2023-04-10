
#include "bt.h"
#include "usb.h"

#include <pico/stdlib.h>
#include <pico/stdio.h>
#include <tusb.h>
#include "pico/cyw43_arch.h"
#include "utils.h"

#include "bt_common.h"

const int interval = 10;
bool bt_started = false;

void bt_init() {
    EVERY(5000);
    if (tud_cdc_connected()) {
        if(bt_started) {
            tud_cdc_write_str("bt started\n");
        } else {
            tud_cdc_write_str("starting bt\n");
            int res = picow_bt_example_init();
            if (res) {
                return;
            }
            tud_cdc_write_str("btstack_main\n");
            btstack_main();
            bt_started = true;
        }
    }
}

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

    while (1) {
        tud();
        hid_task_usb(interval);

        heartbeat();

        bt_init();
        if (bt_started) {
            hid_task_bt(interval);
        }
    }
}
