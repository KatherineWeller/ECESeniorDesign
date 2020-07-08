/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
#ifndef __DRIVERLIB__H_
#define __DRIVERLIB__H_

/* Common Modules */
#include <Include/adc14.h>
#include <Include/aes256.h>
#include <Include/comp_e.h>
#include <Include/cpu.h>
#include <Include/crc32.h>
#include <Include/cs.h>
#include <Include/dma.h>
#include <Include/eusci.h>
#include <Include/fpu.h>
#include <Include/gpio.h>
#include <Include/i2c.h>
#include <Include/interrupt.h>
#include <Include/mpu.h>
#include <Include/pcm.h>
#include <Include/pmap.h>
#include <Include/pss.h>
#include <Include/ref_a.h>
#include <Include/reset.h>
#include <Include/rom.h>
#include <Include/rom_map.h>
#include <Include/rtc_c.h>
#include <Include/spi.h>
#include <Include/systick.h>
#include <Include/timer32.h>
#include <Include/timer_a.h>
#include <Include/uart.h>
#include <Include/wdt_a.h>


/* Device specific modules */
#if defined(__MCU_HAS_SYSCTL_A__)
#include <Include/sysctl_a.h>
#endif

#if defined(__MCU_HAS_SYSCTL__)
#include <Include/sysctl.h>
#endif

#if defined(__MCU_HAS_FLCTL_A__)
#include <Include/flash_a.h>
#endif

#if defined(__MCU_HAS_FLCTL__)
#include <Include/flash.h>
#endif

#if defined(__MCU_HAS_LCD_F__)
#include <Include/lcd_f.h>
#endif

/* Offset Definitions */
#define HWREG8(x)         (*((volatile uint8_t *)(x)))
#define HWREG16(x)        (*((volatile uint16_t *)(x)))
#define HWREG32(x)        (*((volatile uint32_t *)(x)))
#define HWREG(x)          (HWREG16(x))
#define HWREG8_L(x)       (*((volatile uint8_t *)((uint8_t *)&x)))
#define HWREG8_H(x)       (*((volatile uint8_t *)(((uint8_t *)&x)+1)))
#define HWREG16_L(x)      (*((volatile uint16_t *)((uint16_t *)&x)))
#define HWREG16_H(x)      (*((volatile uint16_t *)(((uint16_t *)&x)+1)))


#endif
