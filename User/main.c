#include "stm32f10x.h"      
#include "OLED.h"
#include "W25Q64.h"

int main(void)
{
	uint8_t MID;
	uint16_t DID;

	OLED_Init();
	W25Q64_Init();
	OLED_ShowChar(1,1,'a');

	W25Q64_ReadID(&MID, &DID);
	OLED_ShowHexNum(2,1,MID,2);
	OLED_ShowHexNum(2,5,DID,4);

	while(1)
	{

	}
}

