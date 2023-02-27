#include "24lc16b.h"

#include <stdlib.h>
#include <string.h>

extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly

#define EEPROM_BEGIN 0b1010 << 3 // From datasheet: For the 24LC16B, begin of control byte is set as ‘1010’ binary for read and write operations.
#define EEPROM_MAX_COUNT_OF_PAGES 8 // From datasheet: The device is organized as <eight> blocks of <256> x 8-bit memory
#define EEPROM_PAGE_MAX_COUNT_OF_BYTES 256 // Check comment above

/**
  * @brief  Write to EEPROM an amount of data in blocking mode.
  * @param  pageNumber 24LC16B contains eight page of memory, this parameter chose page.
  * @param  pageByteNumber each page consists of 256 x 8-bit memory, this param chose start bit.
  * @param  Size Amount of data to be write
  */
HAL_StatusTypeDef writeToEEPROM(uint8_t pageNumber, uint8_t pageByteNumber, uint8_t *pData, uint16_t Size){
	if(pageNumber > EEPROM_MAX_COUNT_OF_PAGES)
		return HAL_ERROR;

	if(pageByteNumber + Size >  EEPROM_PAGE_MAX_COUNT_OF_BYTES)
		return HAL_ERROR;

	// First four bit is constant for 24lc16b [1010] then we have three bits of page select
	// and the last bit is set automatically by HAL_I2C_Master_Transmit to <1> therefore we shift address to 1 bit
	uint16_t device_address = (EEPROM_BEGIN | (pageNumber & 0b00000111)) << 1;

	uint8_t *data;
	data = (uint8_t*)malloc(sizeof(uint8_t)*(Size+1));
	data[0] = pageByteNumber;
	memcpy(data+1, pData, Size);

	HAL_StatusTypeDef result = HAL_I2C_Master_Transmit(&hi2c1,device_address, data,Size+1, 100);

	free(data);

	if(result != HAL_OK)
		return result;

	/* We wait until the EEPROM effectively stores data in memory */
	while(HAL_I2C_Master_Transmit(&hi2c1, device_address, 0, 0, HAL_MAX_DELAY) != HAL_OK);

	return HAL_OK;
}

/**
 * @brief check writeToEEPROM brief
 */
HAL_StatusTypeDef readFromEEPROM(uint8_t pageNumber, uint8_t pageByteNumber, uint8_t *pData, uint16_t Size){
	if(pageNumber > EEPROM_MAX_COUNT_OF_PAGES)
		return HAL_ERROR;

	if(pageByteNumber + Size >  EEPROM_PAGE_MAX_COUNT_OF_BYTES)
		return HAL_ERROR;

	// First four bit is constant for 24lc16b [1010] then we have three bits of page select
	// and the last bit is set automatically by HAL_I2C_Master_Transmit to <1> therefore we shift address to 1 bit
	uint16_t device_address = (EEPROM_BEGIN | (pageNumber & 0b00000111)) << 1;

	HAL_StatusTypeDef result = HAL_I2C_Master_Transmit(&hi2c1,device_address, pageByteNumber, 1, 100);

	if(result != HAL_OK)
		return result;

	return HAL_I2C_Master_Receive(&hi2c1,device_address, pData, Size, 100);
}




