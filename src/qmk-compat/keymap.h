#ifndef _KEYMAP_H_
#define _KEYMAP_H_

#include "layout.h"
#include "quantum_keycodes.h"
#include "../matrix.h"

// Ignore
#define PROGMEM

const uint16_t PROGMEM keymaps[2][MATRIX_ROWS][MATRIX_COLS];

// TODO: These are not handled for now
#define KC_LOCK KC_NO

#endif
