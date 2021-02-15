/**
 * \file bsp_spi.h
 * \brief spi外设的参数设置与相关函数声明
 * \author netube_99/netube@163.com
 * \date 2021.02.14
 * \version V1.0
*/

#ifndef _BSP_SPI_H_
#define _BSP_SPI_H_

#include "gd32f1x0.h"
#include "sio.h"//spi通用收发框架

#define SFLASH_SPI                          SPI1
#define SFLASH_SPI_PERCLK                   RCU_SPI1
#define SFLASH_SPI_IRQn                     SPI1_IRQn
#define SFLASH_SPI_PRE_PRIORITY             2//抢断优先级
#define SFLASH_SPI_SUB_PRIORITY             2//响应优先级

#define SFLASH_SPI_GPIO_MOSI_PERCLK         RCU_GPIOB
#define SFLASH_SPI_GPIO_MOSI_PORT           GPIOB
#define SFLASH_SPI_GPIO_MOSI                GPIO_PIN_15
#define SFLASH_SPI_GPIO_MOSI_AF             GPIO_AF_0

#define SFLASH_SPI_GPIO_MISO_PERCLK         RCU_GPIOB
#define SFLASH_SPI_GPIO_MISO_PORT           GPIOB
#define SFLASH_SPI_GPIO_MISO                GPIO_PIN_14
#define SFLASH_SPI_GPIO_MISO_AF             GPIO_AF_0

#define SFLASH_SPI_GPIO_CLK_PERCLK          RCU_GPIOB
#define SFLASH_SPI_GPIO_CLK_PORT            GPIOB
#define SFLASH_SPI_GPIO_CLK                 GPIO_PIN_13
#define SFLASH_SPI_GPIO_CLK_AF              GPIO_AF_0

void SFlash_Init(void);

#endif