#include "board.h"

#include "main.h"

#include <string.h>

static UART_HandleTypeDef huart2;

static void Board_InitLed(void)
{
  GPIO_InitTypeDef gpio_init = {0};

  __HAL_RCC_GPIOD_CLK_ENABLE();

  HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);

  gpio_init.Pin = LD4_Pin;
  gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init.Pull = GPIO_NOPULL;
  gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD4_GPIO_Port, &gpio_init);
}

static void Board_InitUart(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;

  if(HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
}

void Board_Init(void)
{
  Board_InitLed();
  Board_InitUart();
}

void Board_WriteText(const char *text)
{
  HAL_UART_Transmit(&huart2, (const uint8_t *)text, strlen(text), 100);
}

void Board_ApplyAppState(const AppState *state)
{
  HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, state->led_on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}