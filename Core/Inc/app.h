#ifndef APP_H
#define APP_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define APP_SELF_TEST_CHECKSUM 86931263u

typedef struct
{
  uint32_t self_test_checksum;
  uint32_t heartbeat_count;
  bool self_test_passed;
  bool led_on;
} AppState;

void App_Init(AppState *state);
void App_RunSelfTest(AppState *state);
void App_Tick(AppState *state);
void App_FormatSelfTestMessage(const AppState *state, char *buffer, size_t buffer_size);
void App_FormatHeartbeatMessage(const AppState *state, char *buffer, size_t buffer_size);

#endif