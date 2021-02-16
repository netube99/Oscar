/**
 * \file sio.h
 * \brief spi通用收发框架
 * \author netube_99/netube@163.com
 * \date 2021.02.14
 * \version V1.0
*/

#ifndef _SIO_H_
#define _SIO_H_

#include "gd32f1x0.h"

#define SIO_SUCCESS     0x01
#define SIO_ERROR       0x00

typedef struct
{
    uint32_t spi_periph ;//spi外设基地址
    
}sio;

void SIO_Init();
void SIO_IT_Handle(sio *SIO_Handle);

#endif