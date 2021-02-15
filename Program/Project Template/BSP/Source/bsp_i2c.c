#include "bsp_i2c.h"

void I2C_Init(void)
{
    rcu_periph_clock_enable(RCU_I2C1);//I2C外设时钟
    rcu_periph_clock_enable(Board_I2C_GPIO_SDA_PERCLK);//GPIO时钟
    rcu_periph_clock_enable(Board_I2C_GPIO_SCL_PERCLK);//GPIO时钟

    //初始化GPIO

    //设置I2C通信速率与信号占空比
    i2c_clock_config(Board_I2C, 400000, I2C_DTCY_2);
    //设置I2C工作模式，I2C地址长度，I2C地址
    i2c_mode_addr_config(Board_I2C, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, Board_I2C_ADDR);
    //使能I2C ACK
    i2c_ack_config(Board_I2C, I2C_ACK_ENABLE);
    //设置I2C中断使能
    nvic_irq_enable(Board_I2C_EV_IRQn, Board_I2C_PRE_PRIORITY, Board_I2C_SUB_PRIORITY);
    i2c_interrupt_enable(Board_I2C, I2C_INT_EV);
    //使能I2C
    i2c_enable(Board_I2C);
}