/**
 * \file bsp.h
 * \brief 板级支持包管理
 * \author netube_99/netube@163.com
 * \date 2021.01.17
 * \version V1.0
*/

#ifndef _BSP_H_
#define _BSP_H_

#include "gd32f1x0.h"
#include "systick.h"

//BSP库引用管理
#include "bsp_uart.h"//uart
#include "bsp_i2c.h"//i2c
#include "bsp_spi.h"//spi

//BSP选项参数
//中断分组模式默认使用2位抢断2位响应
#define NVIC_PRIGROUP_MODE      NVIC_PRIGROUP_PRE2_SUB2

void BSP_Init(void);//硬件统一初始化

#endif