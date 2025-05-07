/*
 * Application.h
 *
 *  Created on: May 6, 2025
 *      Author: kunal
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "main.h"
#include "Console/Console.h"
#include "GPIO/GPIO.h"
#include "SPI/SPI.h"
#include "../Devices/BME280/BME280.h"
#include "../Devices/W25Qxx_Flash/W25Qxx_Flash.h"
#include "../Middleware/Filesystem/Filesystem.h"




SPI_Config Flash;
W25Qxx_Config Chip1;


void Flash_Init();


#endif /* APPLICATION_H_ */
