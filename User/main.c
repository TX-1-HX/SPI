#include "stm32f10x.h"      
#include "OLED.h"
#include "W25Q64.h"

int main(void)
{
	uint8_t MID;
	uint16_t DID;
	uint8_t SendArray[] = {0x01, 0x02, 0x03, 0x04};
	uint8_t ReceiveArray[4];

	OLED_Init();
	W25Q64_Init();
	OLED_ShowChar(1,1,'a');

	W25Q64_ReadID(&MID, &DID);
	OLED_ShowHexNum(2,1,MID,2);
	OLED_ShowHexNum(2,5,DID,4);

	W25Q64_Sector_Erase(0X000000);
	W25Q64_Page_Program(0X000000, SendArray, 4);
	W25Q64_Read_Data(0X000000, ReceiveArray, 4);
	OLED_ShowHexNum(3, 1, ReceiveArray[0],2);
	OLED_ShowHexNum(3, 4, ReceiveArray[1],2);
	OLED_ShowHexNum(3, 7, ReceiveArray[2],2);
	OLED_ShowHexNum(3, 10, ReceiveArray[3],2);
	while(1)
	{

	}
}

