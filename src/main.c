
#include "bt.h"
#include "usb.h"
#include "matrix.h"

#include <pico/stdlib.h>
#include <pico/stdio.h>
#include <tusb.h>
#include "pico/cyw43_arch.h"
#include "utils.h"
#include "leds.h"
#include "report.h"

#include "bt_common.h"
#include "usb_descriptors.h"

#define POLLING_INTERVAL 1

// Just color everything teal for now
uint16_t leds_status = 0b0011011011011011;
uint8_t report[KB_REPORT_LENGTH] = {0};
uint8_t prev_report[KB_REPORT_LENGTH] = {0};

void heartbeat() {
    EVERY_MS(5000);
    printf(".\n");
}

void on_caps(bool caps) {
    leds_status = caps
        ? (leds_status | U16_LAST_BIT)
        : (leds_status & ~U16_LAST_BIT);
    leds_write(leds_status);
}

void send_reports() {
    EVERY_MS(POLLING_INTERVAL)
    get_report(report, KB_REPORT_LENGTH);
    if (memcmp(prev_report, report, KB_REPORT_LENGTH)) {
        bt_send_report(report, KB_REPORT_LENGTH);
        usb_send_report(report, KB_REPORT_LENGTH);

        memcpy(prev_report, report, KB_REPORT_LENGTH);
    }
}

int main() {
    matrix_init();

    tusb_init();
    stdio_init_all();
    stdio_set_driver_enabled(&stdio_usb, true);
    set_caps_cb(&on_caps);

    leds_init();
    leds_write(leds_status);
    leds_enable(true);

    int res = picow_bt_example_init();
    if (res) {
        return -1;
    }
    bt_init();
    bt_radio_toggle(true);

    while (1) {
        tud_task();

        heartbeat();

        matrix_scan();

        send_reports();
    }
}
