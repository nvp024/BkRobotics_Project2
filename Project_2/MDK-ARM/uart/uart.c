#include "uart.h"
#include <stdio.h>
#define WT901C_BUFFER_SIZE 11 

uint8_t buff[WT901C_BUFFER_SIZE];
static uint8_t uart_len = 0;
static uint8_t uart_flag = 0;
static uint8_t receive_flag = 0;

float roll_angle;
float pitch_angle;
float yaw_angle;

uint8_t unlock[] = {0xFF, 0xAA, 0x69, 0x88, 0xB5};
uint8_t data[] = {0xFF, 0xAA, 0x01, 0x04, 0x00};
uint8_t save[] = {0xFF, 0xAA, 0x00, 0x00, 0x00};
uint8_t command_test[] = {0x00, 0x01, 0x02, 0x03, 0x04};

// Function to receive data via UART (replace with your actual UART receive function)
void data_receive(uint8_t data)
{
	if(data == 0x55 && uart_len == 0)     // Check the condition is the right of one package data 
	{
		receive_flag = 1; 
	}
	
	if(receive_flag)
	{
		if(uart_len == 10)
		{
			buff[uart_len] = data;
			uart_flag = 1;
		}
		else
		{
			buff[uart_len++] = data;
		}
	}
}

// Function to handle the angle from the imu 
void handle()
{
	if(uart_flag)
		{
			if(buff[1] == 0x53)				// Check the condition is the data of angle 
			{
				// Calculate the angle values
				 roll_angle = (float)((short)((short)(buff[3] << 8 ) | buff[2] )) / 32768.0f * 180.0f ;
				 pitch_angle = (float)((short)((short)(buff[5] << 8 ) | buff[4] )) / 32768.0f * 180.0f	;		
				 yaw_angle = (float)((short)((short)(buff[7] << 8 ) | buff[6] )) / 32768.0f * 180.0f ; 
				}	
					receive_flag = 0;
					uart_len = 0;
					uart_flag = 0;
			}
}
void SendData()
{	
		static uint16_t count;
	// STEP 1: Unlock 
	HAL_UART_Transmit(&huart1, unlock, sizeof(unlock), 100);

	// STEP 2: Send the command
	if (HAL_GetTick() - count > 200)
	{
	HAL_UART_Transmit(&huart1, data, 5, 100);
	}
	
	// STEP 3: Save 
	if (HAL_GetTick() - count > 400)
	{
	HAL_UART_Transmit(&huart1, save, sizeof(save), 100);
	}
}