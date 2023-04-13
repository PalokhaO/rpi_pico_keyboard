
#ifndef _BT_H_
#define _BT_H_

#include <pico/stdlib.h>

int bt_init(void);
void bt_radio_toggle(bool enabled);
void bt_send_report(uint8_t *report, size_t report_size);

#endif
