#ifndef BOARD_H
#define BOARD_H

#include "app.h"

void Board_Init(void);
void Board_WriteText(const char *text);
void Board_ApplyAppState(const AppState *state);

#endif