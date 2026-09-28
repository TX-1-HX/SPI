#ifndef __HSPI_H
#define __HSPI_H

void HSPI_Init(void);
void HSPI_W_SCK(uint8_t bitvalue);
void HSPI_W_MOSI(uint8_t bitvalue);
void HSPI_W_CS(uint8_t bitvalue);
uint8_t HSPI_R_MISO(void);
void SPI_BaseConfig_Start(void);
void SPI_BaseConfig_Stop(void);
uint8_t SPI_BaseConfig_SwapData(uint8_t SendData);

#endif
