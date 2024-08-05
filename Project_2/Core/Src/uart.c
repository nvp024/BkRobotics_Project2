#include "uart.h"
#include <stdio.h>
#define WT901C_BUFFER_SIZE 11 

static uint8_t buff[WT901C_BUFFER_SIZE];
static uint8_t uart_len = 0;
static uint8_t uart_flag = 0;
static uint8_t receive_flag = 0;

float roll_angle;
float pitch_angle;
float yaw_angle;

// Function to receive data via UART (replace with your actual UART receive function)
void data_receive(uint8_t data)
{
	if(data == 0x55 && uart_len == 0)
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

void handle()
{
	if(uart_flag)
		{
			if(buff[1] == 0x53)
			{
					// Calculate the angle values
					 roll_angle = (float)((short)((buff[3] << 8 ) | buff[2] )) / 32768 * 180 ;
					 pitch_angle = (float)((short)((buff[5] << 8 ) | buff[4] )) / 32768 * 180	;		
					 yaw_angle = (float)((short)((buff[7] << 8 ) | buff[6] )) / 32768 * 180 ; 
					
					// Now you can use the roll_angle, pitch_angle, and yaw_angle values
					printf("Roll Angle: %.2f degrees\n", roll_angle);
					printf("Pitch Angle: %.2f degrees\n", pitch_angle);
					printf("Yaw Angle: %.2f degrees\n", yaw_angle);
			}	
					receive_flag = 0;
					uart_len = 0;
					uart_flag = 0;
			
			}
}