/**
 * \file bsp.c
 * \brief 板级支持包管理
 * \details Oscar开发板板级支持包子文件统一管理，提供外设初始化管理、底层相关设置函数；
 * \author netube_99/netube@163.com
 * \date 2021.01.17
 * \version V1.0
*/

#include "bsp.h"

//系统底层统一初始化
void BSP_Init(void)
{
    systick_config();//滴答定时器设置
    nvic_priority_group_set(NVIC_PRIGROUP_MODE);//设置中断分组模式
    System_UART_Init();//初始化系统串口
    //ESP8285_UART_Init();//初始化Wi-Fi模块串口
    SFlash_Init();
}