
#ifndef _USB_H_
#define _USB_H_

#include <pico/stdlib.h>

typedef void (*bool_cb) (bool);

void set_caps_cb(bool_cb);
void usb_send_report(uint8_t* report_buf, size_t report_length);

#endif
