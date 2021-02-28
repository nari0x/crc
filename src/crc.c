/*
 * crc.c
 *
 *  Created on: 13 Jan 2021
 *      Author: marcin
 */
#include "crc.h"
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
uint8_t crc8(uint8_t* data,uint8_t size, uint8_t poly){
	uint8_t crc=0;
	while(size--){
		crc^=(uint8_t)*data;
		for(uint8_t i=0;i<8;i++){
			if(crc & 0x80){
				crc=(crc<<1)^poly;
			}
			else crc<<=1;
		}
		data++;
	}
	return crc;
}
/*
uint16_t crc16(uint8_t* data,uint8_t size, uint16_t poly){
	uint16_t crc=0;
	uint16_t sum=0;
	while(size--){
		crc= crc<<8 | *data;
		crc^=sum;
		printf("input crc 0x%04x \n", crc);
		sum= crc & 0xFF00;
		for(uint8_t i=0;i<8;i++){
			if(sum& 0x8000){
				sum=(sum<<1)^poly;
			}else sum<<=1;
		}
		data++;
		printf("sum 0x%04x \n", sum);

	}
	return crc;
}
*/
uint16_t crc16(uint8_t* data,uint8_t size, uint16_t poly){
	uint16_t crc=0;
	uint16_t sum=0;
	uint8_t cnt=size;
	for(uint8_t i=0;i<2;i++){
		crc<<=8;
		if(cnt) {
			crc|= *data++;
			cnt--;
		}
	}
	while(size>0){
		//printf("input crc 0x%04x \n", crc);
		sum= crc & 0xFF00;
		for(uint8_t i=0;i<8;i++){
			if(sum& 0x8000){
				sum=(sum<<1)^poly;
			}else sum<<=1;
		}
		crc<<=8;
		if(size>2) crc|= *data++;
		crc^=sum;
		size--;
	}

	return crc;
}

uint32_t crc32(uint8_t* data,uint8_t size, uint32_t poly){
	uint32_t crc=0;
	uint32_t sum=0;
	uint8_t cnt=size;
	//size to ilosc bajtow z ktorej obliczamy crc

	//always load 4 bytes or load <4 bytes and shift the sfit up to MSB.
	for(uint8_t i=0;i<4;i++){
		crc<<=8;
		if(cnt){
			crc|=*data++;
			cnt--;
		}
	}
	//printf("input crc 0x%08x \n", crc);

	while(size>0){

		sum= crc & 0xFF000000;
		for(uint8_t i=0;i<8;i++){
			if(sum& 0x80000000){
				sum=(sum<<1)^poly;
			}else sum<<=1;
		}
		crc<<=8;
		if(size>4) crc|=*data++;
		crc^=sum;
		size--;
		//printf("crc 0x%08x \n", crc);
	}

	return crc;
}


uint8_t crc8_lookup(uint8_t* data, uint8_t size, uint8_t* pt){
	uint8_t crc=0;
	while(size--){
		printf( " data %d \n",*data);
		//crc^=*data;
		//crc=pt[*data]
		crc=pt[crc^*data]; // above 2 lines written in one
		printf( "0x%02x \n",crc);
		data++;
	}
	return crc;
}

void crc8_t_gen(uint8_t* pt,uint8_t poly){
	uint8_t i,k;
	i=0;
	do{
		//printf("%d \n",i);
		*pt^=i;
		for(k=0;k<8;k++){
			if(*pt & 0x80){
				*pt=(*pt<<1)^poly;
			}
			else *pt<<=1;
		}
		printf("%d \n",*pt);
		pt++;

	}while (i++<255);
}

void crc16_t_gen(uint16_t* pt,uint16_t poly){
	uint8_t i,k;
	i=0;
	do{
		//printf("%d \n",i);
		*pt^=i<<8;
		for(k=0;k<8;k++){
			if(*pt & 0x8000){
				*pt=(*pt<<1)^poly;
			}
			else *pt<<=1;
		}
		//printf("%04X \n",*pt);
		pt++;

	}while (i++<255);
}




void printf_crc_table(const void *pt, uint8_t crc_length){
	for(uint8_t i=0;i<16;i++){
		for(uint8_t k=0;k<16;k++){
			switch (crc_length) {
				case 16:{
					const uint16_t *p16= pt;
					printf("0x%04"PRIx16", ",*p16++);
					pt=p16;
					break;
				}
				case 32:{
					const uint32_t *p32=pt;
					printf("0x%08"PRIx32", ",*p32++);
					pt=p32;
					break;
				}
				default:{
					const uint8_t *p8=pt;
					printf("0x%02"PRIx8", ",*p8++);
					pt=p8;
					break;
				}
			}
		}
		printf("\n");
	}
}


