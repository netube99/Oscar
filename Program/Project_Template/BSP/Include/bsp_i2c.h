/**
 * \file bsp_i2c.h
 * \brief i2c外设的参数设置与相关函数声明
 * \author netube_99/netube@163.com
 * \date 2021.02.07
 * \version V1.0
*/

#ifndef _BSP_I2C_H_
#define _BSP_I2C_H_

#include "bsp.h"

#define Board_I2C                             I2C1
#define Board_I2C_PERCLK                      RCU_I2C1
#define Board_I2C_ADDR                        0xE8
#define Board_I2C_EV_IRQn                     I2C1_EV_IRQn
#define Board_I2C_PRE_PRIORITY                2//抢断优先级
#define Board_I2C_SUB_PRIORITY                2//响应优先级

#define Board_I2C_GPIO_SDA_PERCLK             RCU_GPIOB
#define Board_I2C_GPIO_SDA_PORT               GPIOB
#define Board_I2C_GPIO_SDA_PIN                GPIO_PIN_11
#define Board_I2C_GPIO_SDA_AF                 GPIO_AF_1

#define Board_I2C_GPIO_SCL_PERCLK             RCU_GPIOB
#define Board_I2C_GPIO_SCL_PORT               GPIOB
#define Board_I2C_GPIO_SCL_PIN                GPIO_PIN_10
#define Board_I2C_GPIO_SCL_AF                 GPIO_AF_1

void Board_I2C_Init(void);

#endif