#include "bsp_spi.h"

void SFlash_Init(void)
{
    rcu_periph_clock_enable(SFLASH_SPI_PERCLK);
    rcu_periph_clock_enable(SFLASH_SPI_GPIO_MOSI_PERCLK);
    rcu_periph_clock_enable(SFLASH_SPI_GPIO_MISO_PERCLK);
    rcu_periph_clock_enable(SFLASH_SPI_GPIO_CLK_PERCLK);

    //初始化 GPIO MOSI
    gpio_af_set(SFLASH_SPI_GPIO_MOSI_PORT, SFLASH_SPI_GPIO_MOSI_AF, SFLASH_SPI_GPIO_MOSI);
    gpio_mode_set(SFLASH_SPI_GPIO_MOSI_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, SFLASH_SPI_GPIO_MOSI);
    gpio_output_options_set(SFLASH_SPI_GPIO_MOSI_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SFLASH_SPI_GPIO_MOSI);

    //初始化 GPIO MISO
    gpio_af_set(SFLASH_SPI_GPIO_MISO_PORT, SFLASH_SPI_GPIO_MISO_AF, SFLASH_SPI_GPIO_MISO);
    gpio_mode_set(SFLASH_SPI_GPIO_MISO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, SFLASH_SPI_GPIO_MISO);
    gpio_output_options_set(SFLASH_SPI_GPIO_MISO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SFLASH_SPI_GPIO_MISO);

    //初始化 GPIO CLK
    gpio_af_set(SFLASH_SPI_GPIO_CLK_PORT, SFLASH_SPI_GPIO_CLK_AF, SFLASH_SPI_GPIO_CLK);
    gpio_mode_set(SFLASH_SPI_GPIO_CLK_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, SFLASH_SPI_GPIO_CLK);
    gpio_output_options_set(SFLASH_SPI_GPIO_CLK_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SFLASH_SPI_GPIO_CLK);

    //spi初始化设置
    spi_parameter_struct spi_init_struct;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE ;//时钟采样模式0，clk空闲为0，上升沿采样
    spi_init_struct.device_mode = SPI_MASTER ;//主机模式
    spi_init_struct.endian = SPI_ENDIAN_MSB ;//高位优先
    spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT ;//数据帧大小
    spi_init_struct.nss = SPI_NSS_SOFT ;//软件控制NSS
    spi_init_struct.prescale = SPI_PSC_4 ;//CLK速率分频
    spi_init_struct.trans_mode = SPI_TRANSMODE_FULLDUPLEX ;//全双工传输模式
    spi_init(SFLASH_SPI, &spi_init_struct);//初始化spi外设

    //设置spi中断优先级
    nvic_irq_enable(SFLASH_SPI_PERCLK,SFLASH_SPI_PRE_PRIORITY,SFLASH_SPI_SUB_PRIORITY);
    spi_i2s_interrupt_enable(SFLASH_SPI, SPI_I2S_INT_TBE);
    spi_i2s_interrupt_enable(SFLASH_SPI, SPI_I2S_INT_RBNE);

    //使能SPI
    spi_enable(SFLASH_SPI);
}

void SPI1_IRQHandler(void)
{
    
}
