#include "stm32f10x.h"                  // Device header

void HSPI_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    /*PA4:CS  PA5:SCK  PA6:MISO  PA7:MOSI*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_SetBits(GPIOA,GPIO_Pin_4 | GPIO_Pin_5);
}

void HSPI_W_SCK(uint8_t bitvalue)
{
    GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)bitvalue);
}

void HSPI_W_MOSI(uint8_t bitvalue)
{
    GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)bitvalue);
}

void HSPI_W_CS(uint8_t bitvalue)
{
    GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)bitvalue);
}

uint8_t HSPI_R_MISO(void)
{
    return(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6));
}

void SPI_BaseConfig_Start(void)
{
    HSPI_W_CS(0);
    HSPI_W_SCK(0);
}

void SPI_BaseConfig_Stop(void)
{
    HSPI_W_CS(1);
    HSPI_W_SCK(1);
}

uint8_t SPI_BaseConfig_SwapData(uint8_t SendData)
{
    uint8_t ReceiveData = 0X00;

    /*mode0，在SCK为低电平时移除数据，在SCK第一个边沿移入数据，直至八位*/

    /*掩码的形式发送和接收数据*/
    /*
    for(uint8_t i = 0; i < 8; i++)
    {
        HSPI_W_MOSI(SendData & (0X80 >> i));
        HSPI_W_SCK(1);
        if(HSPI_R_MISO() == 1)
        {
            ReceiveData = ReceiveData|(0X80 >> i);
        }
        HSPI_W_SCK(0);
    }
    return ReceiveData;
    */

    /*交换的形式发送和接收数据*/
    for(uint8_t i = 0; i<8; i++)
    {
        HSPI_W_MOSI(SendData & 0x80);
        SendData = SendData << 1;
        HSPI_W_SCK(1);
        if(HSPI_R_MISO() == 1)
        {
            SendData = (SendData | 0x01);
        }
        HSPI_W_SCK(0);
        ReceiveData = SendData;
    }
    return ReceiveData;
}

