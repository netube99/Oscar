/**
 * \file uio.h
 * \brief 串口收发通用框架相关定义与声明
 * \author netube_99\netube@163.com
 * \date 2021.01.26
 * \version V1.2.0
*/

#ifndef _UIO_H_
#define _UIO_H_

#include "gd32f1x0.h"
#include "ring_buffer.h"

#define UIO_SUCCESS     0x01
#define UIO_ERROR       0x00

typedef struct
{
    uint32_t usart_periph ;//串口外设基地址
    ring_buffer read_rb ;//串口接收环形缓冲区
    ring_buffer write_rb ;//串口发送环形缓冲区
    uint8_t write_busy ;//串口发送状态标志位
    uint8_t read_busy ;//串口接收状态标志位
    uint32_t paragraph_num ;//串口已接收数据段数量
    uint32_t separate_sign ;//段落分隔关键词
    uint8_t separate_sign_size ;//段落分隔关键词长度
}uio;

//串口收发框架初始化
void UIO_Init(uio *UIO_Handle, uint32_t usart_periph,\
                uint32_t separate_sign, uint8_t separate_sign_size,\
                uint8_t *read_buffer_addr, uint32_t read_buffer_size,\
                uint8_t *write_buffer_addr, uint32_t write_buffer_size);
void UIO_IT_Handle(uio *UIO_Handle);//串口中断处理函数
uint8_t UIO_Write_Paragraph(uio *UIO_Handle, void *input_addr, uint32_t lenght);//填充数据段至串口发送缓存区
uint32_t UIO_Read_Paragraph(uio *UIO_Handle, void *output_addr);//从串口接收缓存区读一个数据段
uint32_t UIO_Get_Paragraph_Count(uio *UIO_Handle);//获取串口接收数据包已累积的数量

#endif