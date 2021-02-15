/**
 * \file uio.c
 * \brief 串口收发通用框架
 * \details 
 * \author netube_99\netube@163.com
 * \date 2021.01.27
 * \version V1.1.0
 * 
 * 2021.01.19 V1.0.0 发布第一版本
*/

#include "uio.h"

//串口收发框架初始化函数
void UIO_Init(uio *UIO_Handle, uint32_t usart_periph,\
                uint32_t separate_sign, uint8_t separate_sign_size,\
                uint8_t *read_buffer_addr, uint32_t read_buffer_size,\
                uint8_t *write_buffer_addr, uint32_t write_buffer_size)
{
    UIO_Handle->usart_periph = usart_periph ;//框架与硬件串口基地址绑定
    Ring_Buffer_Init(&(UIO_Handle->read_rb), read_buffer_addr, read_buffer_size);//初始化框架内的接收环形缓冲
    Ring_Buffer_Init(&(UIO_Handle->write_rb), write_buffer_addr, write_buffer_size);//初始化框架内的发送环形缓冲
    UIO_Handle->paragraph_num = 0 ;//初始化接收数据段累加值
    UIO_Handle->read_busy = 0 ;
    UIO_Handle->write_busy = 0 ;
    UIO_Handle->separate_sign = separate_sign ;
    UIO_Handle->separate_sign_size = separate_sign_size ;
}

//串口中断处理函数
void UIO_IT_Handle(uio *UIO_Handle)
{
    //触发了串口写缓冲寄存器空中断
    if(usart_interrupt_flag_get(UIO_Handle->usart_periph, USART_INT_FLAG_TBE) != 0x00)
    {
        if(Ring_Buffer_Get_Lenght(&(UIO_Handle->write_rb)) != 0) //缓冲区有数据未发送完成
        {
            UIO_Handle->write_busy = 1 ;//串口进入发送状态
            //将一个字节从环形缓冲中取出，送到串口发送寄存器；
		    usart_data_transmit(UIO_Handle->usart_periph,Ring_Buffer_Read_Byte(&(UIO_Handle->write_rb)));
        }
        else
        {
            UIO_Handle->write_busy = 0 ;//串口结束发送状态
            usart_interrupt_disable(UIO_Handle->usart_periph, USART_INT_TBE);//数据全部发送完成，关闭串口发送中断
        }
    }

    //触发了串口读缓冲寄存器非空中断
    if(usart_interrupt_flag_get(UIO_Handle->usart_periph, USART_INT_FLAG_RBNE) != 0x00)
    {
		//串口进入接收状态
        UIO_Handle->read_busy = 1 ;
		//获取串口接收数据，数据写到环形缓冲区尾指针
        Ring_Buffer_Write_Byte(&(UIO_Handle->read_rb), usart_data_receive(UIO_Handle->usart_periph));
        //清除中断标志位
        usart_interrupt_flag_clear(UIO_Handle->usart_periph, USART_INT_FLAG_RBNE);
    }

    //触发了串口空闲中断
    if(usart_interrupt_flag_get(UIO_Handle->usart_periph, USART_INT_FLAG_IDLE) != 0x00)
    {
        UIO_Handle->read_busy = 0 ;//串口结束接收状态
        usart_interrupt_flag_clear(UIO_Handle->usart_periph, USART_INT_FLAG_IDLE);
        //将串口接收数据分隔符写入环形缓冲区中：数据A 分隔符 数据B 分隔符
        if(Ring_Buffer_Get_Lenght(&(UIO_Handle->read_rb)) != 0)
        {
            Ring_Buffer_Insert_Keyword(&(UIO_Handle->read_rb), UIO_Handle->separate_sign, UIO_Handle->separate_sign_size);
            UIO_Handle->paragraph_num ++ ;//已接收的数据段 +1
        }
    }
}

//填充数据段至串口发送缓存区
uint8_t UIO_Write_Paragraph(uio *UIO_Handle, void *input_addr, uint32_t lenght)
{
    uint8_t result = Ring_Buffer_Write_String(&(UIO_Handle->write_rb), input_addr, lenght);//填充数据至环形缓冲末尾
    usart_interrupt_enable(UIO_Handle->usart_periph, USART_INT_TBE);//使能写缓冲寄存器空中断（用于逐字节发送数据）
    if(result)
        return UIO_SUCCESS ;
    else 
        return UIO_ERROR ;
}

//数据从串口接收缓存区读取一个数据段
uint32_t UIO_Read_Paragraph(uio *UIO_Handle, void *output_addr)
{
    //从头指针开始搜索到关键字，获得距离，距离 -1 是因为不能读取到关键字上，数据段的结尾在关键字前一个字节
    uint32_t lenght = Ring_Buffer_Find_Keyword(&(UIO_Handle->read_rb), UIO_Handle->separate_sign, UIO_Handle->separate_sign_size) - 1 ;
    Ring_Buffer_Read_String(&(UIO_Handle->read_rb), output_addr, lenght);//读取一个数据段
    Ring_Buffer_Delete(&(UIO_Handle->read_rb), UIO_Handle->separate_sign_size);//删除分隔符
    UIO_Handle->paragraph_num -- ;//已接收的数据段 -1
    return lenght ;
}

//获取串口接收数据包已累积的数量
uint32_t UIO_Get_Paragraph_Count(uio *UIO_Handle)
{
    return UIO_Handle->paragraph_num ;
}