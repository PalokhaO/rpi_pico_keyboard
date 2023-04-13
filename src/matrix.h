
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <pico/stdlib.h>

static uint col_pins[] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15};
static uint row_pins[] = {20,19,18,17,16};

#define MATRIX_COLS sizeof(col_pins)/sizeof(uint)
#define MATRIX_ROWS sizeof(row_pins)/sizeof(uint)

bool matrix_state[MATRIX_ROWS][MATRIX_COLS];

void matrix_init();
void matrix_scan();

#endif
