/*
 * crc.h
 *
 *  Created on: 12 Jan 2021
 *      Author: marcin
 */

#ifndef CRC_H_
#define CRC_H_

#include <stdint.h>
#define TEST_INPUT "123456789"
#define TEST_POLY 0x07

uint8_t crc8_0x07_t[256];
uint16_t crc16_0x1021_t[256];



//***All functions for 8-bit CRC length***
uint8_t crc8(uint8_t* data,uint8_t size, uint8_t poly);
uint8_t crc8_lookup(uint8_t* data, uint8_t size,uint8_t * pt);


//***All functions for 16-bit CRC length***
uint16_t crc16(uint8_t* data,uint8_t size, uint16_t poly);
uint8_t crc16_lookup(void* data, uint8_t poly,uint8_t * t_pointer);


//***All functions for 32-bit CRC length***
uint32_t crc32(uint8_t* data,uint8_t size, uint32_t poly);
uint32_t crc32_lookup(void* data, uint8_t poly,uint8_t * t_pointer);



//tools
void crc8_t_gen(uint8_t* pt,uint8_t poly);
void crc16_t_gen(uint16_t* pt,uint16_t poly);

#endif /* CRC_H_ */
