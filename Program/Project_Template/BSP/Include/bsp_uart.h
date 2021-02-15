/**
 * \file bsp_uart.h
 * \brief 串口外设的参数设置与相关函数声明
 * \author netube_99/netube@163.com
 * \date 2021.01.17
 * \version V1.0
*/

#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#include "gd32f1x0.h"
#include "uio.h"//串口收发框架

//系统串口宏定义
#define SYSTEM_UART                     USART0
#define SYSTEM_UART_Baud                115200
#define SYSTEM_UART_PERCLK              RCU_USART0
#define SYSTEM_UART_IRQn                USART0_IRQn
#define SYSTEM_UART_PRE_PRIORITY        2//抢断优先级
#define SYSTEM_UART_SUB_PRIORITY        2//响应优先级

#define SYSTEM_UART_GPIO_TX_PERCLK      RCU_GPIOA
#define SYSTEM_UART_GPIO_TX_PORT        GPIOA
#define SYSTEM_UART_GPIO_TX_PIN         GPIO_PIN_9
#define SYSTEM_UART_GPIO_TX_AF          GPIO_AF_1

#define SYSTEM_UART_GPIO_RX_PERCLK      RCU_GPIOA
#define SYSTEM_UART_GPIO_RX_PORT        GPIOA
#define SYSTEM_UART_GPIO_RX_PIN         GPIO_PIN_10
#define SYSTEM_UART_GPIO_RX_AF          GPIO_AF_1

#define SYSTEM_UART_READ_BUFFER_SIZE    64
#define SYSTEM_UART_WRITE_BUFFER_SIZE   64
#define SYSTEM_UART_SEPARATE_SIGN       0xABAB2333
#define SYSTEM_UART_SEPARATE_SIGN_SIZE  4

void System_UART_Init(void);//系统串口初始化
uint32_t System_UART_GET_String_Count(void);//获取系统串口指令已接收的数量
uint8_t System_UART_Write_String(void *input_addr);
uint32_t System_UART_Read_String(void *output_addr);

//ESP8285 Wi-Fi模块串口宏定义
#define ESP8285_UART                    USART1
#define ESP8285_UART_Baud               115200
#define ESP8285_UART_PERCLK             RCU_USART1
#define ESP8285_UART_IRQn               USART1_IRQn
#define ESP8285_UART_PRE_PRIORITY       2//抢断优先级
#define ESP8285_UART_SUB_PRIORITY       2//响应优先级
#define ESP8285_UART_READ_BUFFER_SIZE   256
#define ESP8285_UART_WRITE_BUFFER_SIZE  256
#define ESP8285_UART_END_SIGN           '\n'

#define ESP8285_UART_GPIO_TX_PERCLK     RCU_GPIOA
#define ESP8285_UART_GPIO_TX_PORT       GPIOA
#define ESP8285_UART_TX_PIN             GPIO_PIN_2
#define ESP8285_UART_GPIO_TX_AF         GPIO_AF_1

#define ESP8285_UART_GPIO_RX_PERCLK     RCU_GPIOA
#define ESP8285_UART_GPIO_RX_PORT       GPIOA
#define ESP8285_UART_RX_PIN             GPIO_PIN_3
#define ESP8285_UART_GPIO_RX_AF         GPIO_AF_1

void ESP8285_UART_Init(void);//Wi-Fi模块串口初始化

#endif