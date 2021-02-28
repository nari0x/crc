/*
 ============================================================================
 Name        : crc_example.c
 Author      : Marcin
 Version     :
 Copyright   : Your copyright notice
 Description : crc example in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "crc.h"
#include <string.h>
uint8_t crcv8;
uint16_t crcv16;
uint32_t crcv32;
char text[]= "aced";

extern void printf_crc_table(const void* pt, uint8_t crc_length);
int main(void) {


	//crc8_t_gen(crc8_0x07_t,0x07);
	//crc16_t_gen(crc16_0x1021_t, 0x1021);

	//printf_crc_table(crc8_0x07_t,8); //works fine
	//printf_crc_table(crc16_0x1021_t,16); //print ivalid values

	//printf_crc_table(crc8_0x07_t,8);

	//testing crc16
	printf("testing crc16...\n");
	uint8_t i;
	for(i=0;i<5;i++){
		printf("liczba elementow tablicy %d. Wartosc crc: ", i);
		crcv16=crc16(text, i, 0x1021);
		printf("crc value is.. 0x%04X \n", crcv16);
	}
	//testing crc32
	printf("testing crc32...\n");
	for(i=0;i<5;i++){
		printf("liczba elementow tablicy %d. Wartosc crc: ", i);
		crcv32=crc32(text, i, 0x4C11DB7);
		printf("crc value is.. 0x%08X \n", crcv32);
	}

	//crc=crc8_lookup(text,2,crc8_0x07_t);
	//crcv16= crc16(text,4,0x1021);

	return EXIT_SUCCESS;
}
