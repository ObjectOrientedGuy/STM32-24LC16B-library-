#include "stm32f4xx_hal.h"

HAL_StatusTypeDef writeToEEPROM(uint8_t pageNumber, uint8_t pageByteNumber, uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef readFromEEPROM(uint8_t pageNumber, uint8_t pageByteNumber, uint8_t *pData, uint16_t Size);
