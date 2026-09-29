#ifndef __W25Q64_H
#define __W25Q64_H

void W25Q64_Init(void);
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID);
void W25Q64_Write_Enable(void);
void W25Q64_Wait_Busy(void);
void W25Q64_Page_Program(uint32_t Address, uint8_t *SendArray, uint16_t count);
void W25Q64_Sector_Erase(uint32_t Address);
void W25Q64_Read_Data(uint32_t Address, uint8_t *ReceiveArray, uint32_t count);

#endif
