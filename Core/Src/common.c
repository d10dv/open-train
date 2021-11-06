#include "common.h"

#include "main.h"
#include "usart.h"
#include "stdio.h"
#include <string.h>

void debugPrint(const char *str)
{
    char transmitStr[80];
    sprintf(transmitStr, "%s \r\n", str);
    HAL_UART_Transmit(&huart1, (uint8_t *)transmitStr, strlen(transmitStr), 100);
}