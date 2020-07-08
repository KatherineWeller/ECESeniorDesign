/*
 * LCD_SPI.h
 *
 *  Created on: Mar 10, 2020
 *      Author: kattw
 */

#ifndef LCD_SPI_H_
#define LCD_SPI_H_

#include <stdint.h>

extern void SPI_init(void);
extern void SPI_fastMode(void);
extern void SPI_ReadBuffer(uint8_t *pBuffer, uint32_t size);
extern void SPI_Write(uint8_t data);
extern void SPI_WriteBuffer(uint8_t *buff, uint32_t Transfersize);
extern void SPI_Enable(void);
extern void SPI_Disable(void);

#endif /* LCD_SPI_H_ */
