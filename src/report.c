#include "report.h"
#include "qmk-compat/keymap.h"
#include <stdio.h>
#include <string.h>

uint16_t get_keycode(int i, int j, int layer) {
    uint16_t keycode = keymaps[layer][i][j];
    if (keycode == KC_TRNS) {
        return layer
            ? get_keycode(i, j, layer - 1)
            : KC_NO;
    } else {
        return keycode;
    }
}

void get_report_with_layer(uint8_t *buf, size_t buf_len, int layer) {
    memset(buf, 0, buf_len);
    int curr_report_byte = 2;
    uint16_t keycode;

    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLS; j++) {
            if (matrix_state[i][j]) {
                keycode = get_keycode(i, j, layer);
                printf("Keycode: %x\n", keycode);
                if (keycode && IS_QK_BASIC(keycode) && curr_report_byte < buf_len) {
                    buf[curr_report_byte] = keycode;
                    curr_report_byte++;
                } else if (IS_QK_MODS(keycode)) {
                    buf[0] |= QK_MODS_GET_MODS(keycode);
                } else if (IS_QK_MOMENTARY(keycode)) {
                    int new_layer = QK_MOMENTARY_GET_LAYER(keycode);
                    if (new_layer != layer) {
                        get_report_with_layer(buf, buf_len, new_layer);
                        return;
                    }
                }
            }
        }
    }
}

void get_report(uint8_t *buf, size_t buf_len) {
    get_report_with_layer(buf, buf_len, 0);
}