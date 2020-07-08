/*
 * LCD_SPI.c
 *
 *  Created on: Mar 10, 2020
 *      Author: kattw
 */

#include "msp432.h"
#include "msp.h"
#include "LCD_SPI.h"

// Pins from MSP432 connected to the LCD
//#define SPI_SIMO        BIT6  //P1.6
//#define SPI_SOMI        BIT7  //P1.7
//#define SPI_CLK         BIT5  //P1.5

// Ports
//#define SPI_DIR         P1DIR
//#define SPI_OUT         P1OUT
//#define SPI_REN         P1REN

/*
void SPI_init(){
    // Port initialization for LCD operation
    // Configure SCLK for USCI B0 peripheral module operation.

    P1SEL0 |= SPI_CLK;
    P1SEL1 &= ~SPI_CLK;

    // Configure MISO for USCI B0 peripheral module operation.
    P1SEL0  |= SPI_SOMI;
    P1SEL1 &= ~SPI_SOMI;

    // Configure MOSI for USCI B0 peripheral module operation.
    P1SEL0  |= SPI_SIMO;
    P1SEL1 &= ~SPI_SIMO;

    P1SEL0 |= SPI_CLK + SPI_SOMI + SPI_SIMO;
    SPI_DIR |= SPI_CLK + SPI_SIMO;                         //THIS MIGHT BE UNNECESSARY****
    SPI_REN |= SPI_SOMI;                                   // Pull-Ups on SD Card SOMI
    SPI_OUT |= SPI_SOMI;                                   // Certain SD Card Brands need pull-ups

    //Set P5.5 as USCI B0 STE since P1.4 is taken by a mf button
    //Set P5.4 as TFT RST
    P5DIR |= BIT4 + BIT5;

    // Initialize USCI_B0 for SPI Master operation
    UCB0CTL1 |= UCSWRST;                                                 // Put state machine in reset
    UCB0CTL0 = UCCKPL | UCMSB | UCMST | UCMODE_0 | UCSYNC;               // 3-pin, 8-bit SPI master

    // Clock polarity select - The inactive state is high
    // MSB first
    UCB0CTL1 = UCSWRST | UCSSEL_2;                         // Use SMCLK, keep RESET
    UCB0BR0 = 1;                                           //Alternate SPI clock frequency = 625 kHz
    //UCB0BR0 = 63;                                        // Initial SPI clock must be <400kHz
    UCB0BR1 = 0;                                           // f_UCxCLK = 25MHz/63 = 397kHz
    UCB0CTL1 &= ~UCSWRST;                                  // Release USCI state machine
    UCB0IFG &= ~UCRXIFG;

    // Enable SPI RX Interrupt for UCB0
    //UCB0IE |= UCRXIE;
}
*/

void SPI_fastMode(void)
{
    UCB0CTL1 |= UCSWRST;                                   // Put state machine in reset
    UCB0BR0 = 2;                                           // f_UCxCLK = 25MHz/2 = 12.5MHz
    UCB0BR1 = 0;
    UCB0CTL1 &= ~UCSWRST;                                  // Release USCI state machine
}

void SPI_Write(uint8_t data)
{
        __disable_interrupts();                                 // Make this operation atomic

        // Clock the actual data transfer and send the bytes. Note that we
        // intentionally not read out the receive buffer during frame transmission
        // in order to optimize transfer speed, however we need to take care of the
        // resulting overrun condition.

        while (!(UCB0IFG & UCTXIFG));                      // Wait while not ready for TX
        UCB0TXBUF = data;                                  // Write byte

        while (!UCRXIFG);                                     //Wait until RX complete flag is set
        UCB0RXBUF;                                             // Dummy read to empty RX buffer
                                                               // and clear any overrun conditions
        __enable_interrupts();
}

void SPI_WriteBuffer(uint8_t *buff, uint32_t Transfersize)
{
        __disable_interrupts();                                 // Make this operation atomic

        // Clock the actual data transfer and send the bytes. Note that we
        // intentionally not read out the receive buffer during frame transmission
        // in order to optimize transfer speed, however we need to take care of the
        // resulting overrun condition.
        while (Transfersize--){
            while (!(UCB0IFG & UCTXIFG)) ;                     // Wait while not ready for TX
            UCB0TXBUF = *buff++;                            // Write byte
        }
        while (!UCRXIFG);                                     //Wait until RX complete flag is set
        UCB0RXBUF;                                             // Dummy read to empty RX buffer
                                                               // and clear any overrun conditions

        __enable_interrupts();
}

void SPI_ReadBuffer(uint8_t *pbuffer, uint32_t size)
{
    __disable_interrupts();                                 // Make this operation atomic

    UCB0IFG &= ~UCRXIFG;                                   // Ensure RXIFG is clear

    // Clock the actual data transfer and receive the bytes
    while (size--){
        while (!(UCB0IFG & UCTXIFG));                     // Wait while not ready for TX
        UCB0TXBUF = 0xff;                                  // Write dummy byte

        while(!UCRXIFG);                                     //Wait until RX complete flag is set
        *pbuffer++ = UCB0RXBUF;
    }

    __enable_interrupts();
}

void SPI_Enable(void)
{
    P5OUT &= ~BIT2;
}

void SPI_Disable(void)
{
    P5OUT = BIT2;
}
