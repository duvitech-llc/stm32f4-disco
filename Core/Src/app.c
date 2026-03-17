#include "app.h"

#include <stdio.h>

static uint32_t App_CalculateChecksum(void)
{
  static const uint8_t sample_data[] = { 3u, 1u, 4u, 1u, 5u, 9u };
  uint32_t checksum = 0u;
  size_t index;

  for(index = 0u; index < sizeof(sample_data); ++index)
  {
    checksum = (checksum * 31u) + sample_data[index];
  }

  return checksum;
}

void App_Init(AppState *state)
{
  state->self_test_checksum = 0u;
  state->heartbeat_count = 0u;
  state->self_test_passed = false;
  state->led_on = false;
}

void App_RunSelfTest(AppState *state)
{
  state->self_test_checksum = App_CalculateChecksum();
  state->self_test_passed = (state->self_test_checksum == APP_SELF_TEST_CHECKSUM);
}

void App_Tick(AppState *state)
{
  state->heartbeat_count += 1u;
  state->led_on = !state->led_on;
}

void App_FormatSelfTestMessage(const AppState *state, char *buffer, size_t buffer_size)
{
  snprintf(buffer,
           buffer_size,
           "SELFTEST:%s checksum=%lu\r\n",
           state->self_test_passed ? "PASS" : "FAIL",
           (unsigned long)state->self_test_checksum);
}

void App_FormatHeartbeatMessage(const AppState *state, char *buffer, size_t buffer_size)
{
  snprintf(buffer,
           buffer_size,
           "HEARTBEAT:%lu led=%u\r\n",
           (unsigned long)state->heartbeat_count,
           state->led_on ? 1u : 0u);
}