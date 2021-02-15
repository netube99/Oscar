/**
 * \file bsp_uart.c
 * \brief 串口外设相关函数的实现
 * \details Oscar A开发板上有两个UART通信接口；
 * UART0连接至CP2102串口转USB，用于开发板与PC的串口通信；
 * UART1用于主控与ESP8285 Wi-Fi模块的通信，通过串口传输AT指令或透传数据；
 * 本库提供了串口参数的设置宏、初始化函数和中断/阻塞收发等串口操作函数；
 * \author netube_99\netube@163.com
 * \date 2021.01.17
 * \version V1.0
*/

#include "bsp_uart.h"

uint8_t system_uart_read_buffer[SYSTEM_UART_READ_BUFFER_SIZE];//系统串口接收环形缓冲区
uint8_t system_uart_write_buffer[SYSTEM_UART_WRITE_BUFFER_SIZE];//系统串口发送环形缓冲区
uio system_uart_uio ;//系统串口收发框架

/**
 * \brief 系统串口外设初始化
 * \param IT_Config: 是否启用串口中断功能
 *      \arg UART_IT_ENABLE: 启用串口中断
 *      \arg UART_IT_DISABLE: 不启用串口中断
 * \return 无
*/
void System_UART_Init(void)
{
    //开启外设时钟
    rcu_periph_clock_enable(SYSTEM_UART_PERCLK);//使能串口时钟
    rcu_periph_clock_enable(SYSTEM_UART_GPIO_TX_PERCLK);//使能GPIO时钟
    rcu_periph_clock_enable(SYSTEM_UART_GPIO_RX_PERCLK);//使能GPIO时钟

    //TX IO设置
    gpio_af_set(SYSTEM_UART_GPIO_TX_PORT, SYSTEM_UART_GPIO_TX_AF, SYSTEM_UART_GPIO_TX_PIN);//设置复用功能组
    gpio_mode_set(SYSTEM_UART_GPIO_TX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, SYSTEM_UART_GPIO_TX_PIN);//AF复用模式，内部上拉
    gpio_output_options_set(SYSTEM_UART_GPIO_TX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SYSTEM_UART_GPIO_TX_PIN);//推挽输出，50M高速模式

    //RX IO设置
    gpio_af_set(SYSTEM_UART_GPIO_RX_PORT, SYSTEM_UART_GPIO_RX_AF, SYSTEM_UART_GPIO_RX_PIN);//设置复用功能组
    gpio_mode_set(SYSTEM_UART_GPIO_RX_PORT,GPIO_MODE_AF, GPIO_PUPD_NONE, SYSTEM_UART_GPIO_RX_PIN);//AF复用模式，无上下拉

    //串口设置
    usart_baudrate_set(SYSTEM_UART, SYSTEM_UART_Baud);//设置波特率
    usart_transmit_config(SYSTEM_UART, USART_TRANSMIT_ENABLE);//使能串口输出
    usart_receive_config(SYSTEM_UART, USART_RECEIVE_ENABLE);//使能串口输入
    usart_enable(SYSTEM_UART);//启用串口

    //初始化系统串口收发框架
    UIO_Init(&system_uart_uio, SYSTEM_UART,\
            SYSTEM_UART_SEPARATE_SIGN, SYSTEM_UART_SEPARATE_SIGN_SIZE,\
            system_uart_read_buffer, SYSTEM_UART_READ_BUFFER_SIZE,\
            system_uart_write_buffer, SYSTEM_UART_WRITE_BUFFER_SIZE);
			
	//串口中断设置
    nvic_irq_enable(SYSTEM_UART_IRQn, SYSTEM_UART_PRE_PRIORITY, SYSTEM_UART_SUB_PRIORITY);//开启串口中断
    usart_interrupt_enable(SYSTEM_UART, USART_INT_TBE);//使能写缓冲寄存器空中断（用于逐字节发送数据）
    usart_interrupt_enable(SYSTEM_UART, USART_INT_RBNE);//使能读缓冲寄存器非空中断（用于逐字节接收数据）
    usart_interrupt_enable(SYSTEM_UART, USART_INT_IDLE);//使能串口空闲中断（用于分隔上一段数据和下一段数据）
}

void USART0_IRQHandler(void)
{
    UIO_IT_Handle(&system_uart_uio);
}

//获取系统串口已接收数据段的数量
uint32_t System_UART_GET_String_Count(void)
{
    return UIO_Get_Paragraph_Count(&system_uart_uio);
}

//系统串口发送数据
uint8_t System_UART_Write_String(void *input_addr)
{
    return UIO_Write_Paragraph(&system_uart_uio, input_addr, strlen(input_addr));
}

//读取一条以结束符分隔的串口指令
uint32_t System_UART_Read_String(void *output_addr)
{
    uint32_t lenght = UIO_Read_Paragraph(&system_uart_uio, output_addr);
    *((uint8_t *)output_addr + lenght) = '\0';
	return lenght ;
}

uint8_t esp8285_uart_read_buffer[ESP8285_UART_READ_BUFFER_SIZE];//esp8285串口接收环形缓冲区
uint8_t esp8285_uart_write_buffer[ESP8285_UART_WRITE_BUFFER_SIZE];//esp8285串口发送环形缓冲区
uio esp8285_uart_uio ;//esp8285串口收发框架

//ESP8285 Wi-Fi模块通信串口初始化
void ESP8285_UART_Init(void)
{
    //开启外设时钟
    rcu_periph_clock_enable(ESP8285_UART_PERCLK);//串口时钟
    rcu_periph_clock_enable(ESP8285_UART_GPIO_TX_PERCLK);//GPIO时钟
    rcu_periph_clock_enable(ESP8285_UART_GPIO_RX_PERCLK);//GPIO时钟

    //TX IO设置
    gpio_af_set(ESP8285_UART_GPIO_TX_PORT, ESP8285_UART_GPIO_TX_AF, ESP8285_UART_TX_PIN);//设置复用功能组
    gpio_mode_set(ESP8285_UART_GPIO_TX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, ESP8285_UART_TX_PIN);//AF复用模式，内部上拉
    gpio_output_options_set(ESP8285_UART_GPIO_TX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, ESP8285_UART_TX_PIN);//推挽输出，50M高速模式

    //RX IO设置
    gpio_af_set(ESP8285_UART_GPIO_RX_PORT, ESP8285_UART_GPIO_RX_AF, ESP8285_UART_RX_PIN);//设置复用功能组
    gpio_mode_set(ESP8285_UART_GPIO_RX_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, ESP8285_UART_RX_PIN);//AF复用模式，无上下拉

    //串口设置
    usart_baudrate_set(ESP8285_UART, ESP8285_UART_Baud);//设置波特率
    usart_transmit_config(ESP8285_UART, USART_TRANSMIT_ENABLE);//使能串口输出
    usart_receive_config(ESP8285_UART, USART_RECEIVE_ENABLE);//使能串口输入
    usart_enable(ESP8285_UART);//启用串口

    //串口中断设置
    nvic_irq_enable(ESP8285_UART_IRQn, SYSTEM_UART_PRE_PRIORITY, SYSTEM_UART_SUB_PRIORITY);//开启串口中断
    usart_interrupt_enable(ESP8285_UART, USART_INT_TBE);//使能写缓冲寄存器空中断
    usart_interrupt_enable(ESP8285_UART, USART_INT_RBNE);//使能读缓冲寄存器非空中断
}

void USART1_IRQHandler(void)
{
    UIO_IT_Handle(&esp8285_uart_uio);
}
