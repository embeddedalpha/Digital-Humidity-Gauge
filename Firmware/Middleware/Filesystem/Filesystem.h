/*
 * Filesystem.h
 *
 *  Created on: May 5, 2025
 *      Author: kunal
 */

#ifndef FILESYSTEM_FILESYSTEM_H_
#define FILESYSTEM_FILESYSTEM_H_

#include "main.h"



typedef struct FileSystem_Typedef
{
	uint8_t ID;
	char *Name;
	uint8_t Size;
	uint32_t Starting_Address;

}FileSystem_Typedef;




#endif /* FILESYSTEM_FILESYSTEM_H_ */
