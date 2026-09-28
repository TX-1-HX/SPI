#include "stm32f10x.h"                  // Device header
#include "HSPI.h"

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
