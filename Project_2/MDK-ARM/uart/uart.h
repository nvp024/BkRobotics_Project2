#ifndef UART_H
#define UART_H
#include <stdint.h>
#include "main.h"

extern UART_HandleTypeDef huart1;

void data_receive(uint8_t data);
void handle(); 
void SendData(uint8_t* command, int length, UART_HandleTypeDef* huart);

#endif