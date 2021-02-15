#include "main.h"

uint8_t get[64];

int main(void)
{
	BSP_Init();//底层统一初始化
    while(1)
    {
        if(System_UART_GET_String_Count() != 0)
        {
			//System_UART_Write_String("reading\r\n");
            System_UART_Read_String(get);
			//System_UART_Write_String("printing\r\n");
            System_UART_Write_String(get);
        }
    }
}
