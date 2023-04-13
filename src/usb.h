
#ifndef _USB_H_
#define _USB_H_

#include <pico/stdlib.h>

typedef void (*bool_cb) (bool);

void set_caps_cb(bool_cb);
void hid_task_usb(int interval_ms);

#endif
