# STM32-24LC16B-library

# Example:
Example for STM32F4DISCOVERY. 

Connect EEPROM:

        A0,1,2 (PIN 1,2,3) -> not connected
               Vss (PIN 4) -> GND
               SDA (PIN 5) -> PB7 (pull-up to 3V)
               SCL (PIN 6) -> PB6 (pull-up to 3V)
               WP  (PIN 7) -> GND
               Vcc (PIN 8) -> 3V
               
main.h:

        #include <string.h>
        #include "24lc16b.h"
        
        ...
        
        const char wmsg[14] = "We love STM32!";
        char rmsg[14];
        writeToEEPROM(2, 2, (uint8_t*)wmsg, 14);
        readFromEEPROM(2, 2, (uint8_t*)rmsg, 14);

        if(strcmp(wmsg, rmsg) == 0) {
                while(1) {
                        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
                        HAL_Delay(100);
                }
        }
        
        

![untitled](https://user-images.githubusercontent.com/74777523/221693956-cfcc9215-3ed3-493d-991d-dce325fe1560.png)
