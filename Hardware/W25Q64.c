#include "stm32f10x.h"                  // Device header
#include "HSPI.h"
#include "W25Q64_Register.h"

void W25Q64_Init(void)
{
    HSPI_Init();
}

void W25Q64_ReadID(uint8_t *MID, uint16_t *DID)
{
    SPI_BaseConfig_Start();
    SPI_BaseConfig_SwapData(0X9F);
    *MID = SPI_BaseConfig_SwapData(0XFF);
    *DID = SPI_BaseConfig_SwapData(0XFF);
    *DID = *DID << 8;
    *DID  = *DID | SPI_BaseConfig_SwapData(0XFF);
    SPI_BaseConfig_Stop();
}

void W25Q64_Write_Enable(void)
{
    SPI_BaseConfig_Start();
    SPI_BaseConfig_SwapData(Write_Enable);
    SPI_BaseConfig_Stop();
}

void W25Q64_Wait_Busy(void)
{
    SPI_BaseConfig_Start();
    SPI_BaseConfig_SwapData(Read_Status_Register_1);
    while((SPI_BaseConfig_SwapData(0XFF) & 0X01) == 0x01);      //0即为不忙状态
    SPI_BaseConfig_Stop();
}

void W25Q64_Page_Program(uint32_t Address, uint8_t *SendArray, uint16_t count)
{
    W25Q64_Write_Enable();

    SPI_BaseConfig_Start();
    SPI_BaseConfig_SwapData(Page_Program);
    SPI_BaseConfig_SwapData(Address >> 16);
    SPI_BaseConfig_SwapData(Address >> 8);
    SPI_BaseConfig_SwapData(Address);
    for(uint16_t i = 0; i < count; i++)
    {
        SPI_BaseConfig_SwapData(SendArray[i]);
    }
    SPI_BaseConfig_Stop();

    W25Q64_Wait_Busy();
}

void W25Q64_Sector_Erase(uint32_t Address)
{
    W25Q64_Write_Enable();

    SPI_BaseConfig_Start();
    SPI_BaseConfig_SwapData(Sector_Erase);
    SPI_BaseConfig_SwapData(Address >> 16);
    SPI_BaseConfig_SwapData(Address >> 8);
    SPI_BaseConfig_SwapData(Address);
    SPI_BaseConfig_Stop();

    W25Q64_Wait_Busy();
}

void W25Q64_Read_Data(uint32_t Address, uint8_t *ReceiveArray, uint32_t count)
{
    SPI_BaseConfig_Start();
    SPI_BaseConfig_SwapData(Read_Data);
    SPI_BaseConfig_SwapData(Address >> 16);
    SPI_BaseConfig_SwapData(Address >> 8);
    SPI_BaseConfig_SwapData(Address);
    for(uint32_t i = 0; i < count; i++)
    {
        ReceiveArray[i] = SPI_BaseConfig_SwapData(0xFF);
    }
    SPI_BaseConfig_Stop();
}
