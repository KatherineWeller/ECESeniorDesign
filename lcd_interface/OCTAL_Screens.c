/*
 * OCTAL_Screens.c
 * Contains Screen Creation Functions for OCTAL Project
 *  Created on: Mar 15, 2020
 *      Author: kattw
 */

#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include <msp432.h>
#include "Bitmaps.h"
#include "LCD_Spi.h"
#include "Eve2_81x.h"
#include "hw_api.h"
#include "MatrixEve2Conf.h"

#define COPYBUFSIZE 64

uint32_t BIT_BASE_ADDR = RAM_G + 0x40000UL;     //Create a base address for storing bitmaps in EVE RAM

uint32_t Load_RAWH(uint32_t BASE_BIT_ADDR, uint8_t rawh[], uint32_t size){
    uint32_t ADDR_ADD = BASE_BIT_ADDR; uint16_t BLOCK_SIZE = 0;
    uint32_t REMAINING_BYTES = size; uint8_t COPY_BUF[COPYBUFSIZE] = {0};
    int i = 0, j = 0;

    while(REMAINING_BYTES){
        if(REMAINING_BYTES > COPYBUFSIZE){
            BLOCK_SIZE = COPYBUFSIZE;
        }
        else{
            BLOCK_SIZE = REMAINING_BYTES;
        }
        for(i = 0; i < COPYBUFSIZE; i ++){
            j = (size-REMAINING_BYTES+i);
            COPY_BUF[i] = rawh[j];
        }
        ADDR_ADD = WriteBlockRAM(ADDR_ADD, COPY_BUF, BLOCK_SIZE);
        REMAINING_BYTES -= BLOCK_SIZE;
    }
    return(ADDR_ADD);
}

void InitLEDGPio(){
    P2DIR = 0xFF;      //Set PORT2 for LED Port output pins
    P2OUT = 0x00;
}

void MakeScreen_Loading(){
    Send_CMD(CMD_DLSTART);                              //Start a new display list
    Send_CMD(CLEAR_COLOR_RGB(0, 0, 0));                 //Determine the clear screen color
    Send_CMD(CLEAR(1, 1, 1));                           //Clear the screen and the current display list
    Cmd_Text(DWIDTH / 2, DHEIGHT / 4, 31, OPT_CENTER, "Loading...");
    Cmd_Spinner(DWIDTH / 2, DHEIGHT / 2, 0, 0);
    Send_CMD(DISPLAY());                                //End the display list
    Send_CMD(CMD_SWAP);                                 //Swap commands into RAM
    __delay_cycles(100);
    UpdateFIFO();                                       // Trigger the CoProcessor to start processing the FIFO
}

void MakeScreen_OctalLogo(){
    Send_CMD(CMD_DLSTART);                              //Start a new display list
    Send_CMD(CLEAR_COLOR_RGB(0, 0, 0));                 //Determine the clear screen color
    Send_CMD(CLEAR(1, 1, 1));                           //Clear the screen and the current display list
    Cmd_Gradient(0, 100, 0x000000, 0, 272, 0x808080);
    Send_CMD(COLOR_RGB(255, 255, 255));                 //Change color to white for text
    Cmd_Text(340, 40, 31, OPT_CENTER, "OCTAL");

    Load_RAWH(BIT_BASE_ADDR, octal_logo_raw, sizeof(octal_logo_raw));

    Send_CMD(BITMAP_SOURCE(BIT_BASE_ADDR));
    Send_CMD(BITMAP_LAYOUT(ARGB2, 256, 85));
    Send_CMD(BITMAP_SIZE(NEAREST, BORDER, BORDER, 256, 85));
    Send_CMD(BEGIN(BITMAPS));
    Send_CMD(VERTEX2II(0, 0, 0, 0));
    Send_CMD(END());
    Send_CMD(DISPLAY());                                //End the display list
    Send_CMD(CMD_SWAP);                                 //Swap commands into RAM
    __delay_cycles(100);
    UpdateFIFO();                                       // Trigger the CoProcessor to start processing the FIFO
}

void MakeScreen_Tutorial_Page1(){
    Send_CMD(CMD_DLSTART);                              //Start a new display list
    Send_CMD(CLEAR_COLOR_RGB(0, 0, 0));                 //Determine the clear screen color
    Send_CMD(CLEAR(1, 1, 1));                           //Clear the screen and the current display list
    Cmd_Gradient(0, 100, 0x000000, 0, 272, 0x808080);

    Send_CMD(COLOR_RGB(255, 255, 255));                 //Change color to white for text
    Cmd_Text(140, 40, 31, OPT_CENTER, "How to play:");
    Cmd_Text(120, 120, 27, OPT_CENTER, "Use purple buttons to add");
    Cmd_Text(120, 140, 27, OPT_CENTER, " sound effects and notes");
    Cmd_Text(120, 160, 27, OPT_CENTER, "during PLAY or RECORD mode");

    Cmd_FGcolor(0x9400d3);
    Cmd_BGcolor(0xC0C0C0);
    Send_CMD(COLOR_RGB(0, 0, 0));                       //Change color to black for text
    Cmd_Keys(250, 100, 50, 200, 30, 0, "OOO");
    Cmd_Keys(250, 155, 50, 200, 30, 0, "OOO");
    Cmd_Keys(250, 210, 50, 200, 30, 0, "OOO");

    Send_CMD(DISPLAY());                                //End the display list
    Send_CMD(CMD_SWAP);                                 //Swap commands into RAM
    __delay_cycles(100);
    UpdateFIFO();                                       // Trigger the CoProcessor to start processing the FIFO
}

void MakeScreen_Tutorial_Page2(){
    Send_CMD(CMD_DLSTART);                              //Start a new display list
    Send_CMD(CLEAR_COLOR_RGB(0, 0, 0));                 //Determine the clear screen color
    Send_CMD(CLEAR(1, 1, 1));                           //Clear the screen and the current display list
    Cmd_Gradient(0, 100, 0x000000, 0, 272, 0x808080);

    Send_CMD(COLOR_RGB(255, 255, 255));                 //Change color to white for text
    Cmd_Text(140, 40, 31, OPT_CENTER, "How to play:");
    Cmd_Text(170, 120, 27, OPT_CENTER, "Enable ECHO or REVERB during PLAY mode");
    Cmd_Text(150, 140, 27, OPT_CENTER, "using these corresponding keys -->");


    Cmd_FGcolor(0xD3D3D3);
    Cmd_BGcolor(0xA9A9A9);
    Send_CMD(COLOR_RGB(0, 0, 0));                       //Change color to black for text
    Cmd_Keys(370, 100, 50, 70, 30, 0, "E");
    Cmd_Keys(370, 160, 50, 70, 30, 0, "R");


    Send_CMD(DISPLAY());                                //End the display list
    Send_CMD(CMD_SWAP);                                 //Swap commands into RAM
    __delay_cycles(100);
    UpdateFIFO();                                       // Trigger the CoProcessor to start processing the FIFO
}

void MakeScreen_OctalLogo_xStart(){
    Send_CMD(CMD_DLSTART);                              //Start a new display list
    Send_CMD(CLEAR_COLOR_RGB(0, 0, 0));                 //Determine the clear screen color
    Send_CMD(CLEAR(1, 1, 1));                           //Clear the screen and the current display list
    Cmd_Gradient(0, 100, 0x000000, 0, 272, 0x808080);   //Display black to gray gradient

    Send_CMD(COLOR_RGB(255, 255, 255));                 //Change color to white for text
    Cmd_Text(340, 40, 31, OPT_CENTER, "OCTAL");

    Send_CMD(COLOR_RGB(148, 0, 211));                   //Change color to green for text
    Cmd_Text(DWIDTH / 2, DHEIGHT / 2, 31, OPT_CENTER, "Press GO to Begin");

    Send_CMD(COLOR_RGB(255, 255, 255));                 //Change color to white for text
    Send_CMD(BITMAP_SOURCE(BIT_BASE_ADDR));
    Send_CMD(BITMAP_LAYOUT(ARGB2, 256, 85));
    Send_CMD(BITMAP_SIZE(NEAREST, BORDER, BORDER, 256, 85));
    Send_CMD(BEGIN(BITMAPS));
    Send_CMD(VERTEX2II(0, 0, 0, 0));
    Send_CMD(END());
    Send_CMD(DISPLAY());                                //End the display list
    Send_CMD(CMD_SWAP);                                 //Swap commands into RAM
    __delay_cycles(100);
    UpdateFIFO();                                       // Trigger the CoProcessor to start processing the FIFO
}

void MakeScreen_Prompt_PLAY_RECORD(){
    Send_CMD(CMD_DLSTART);                              //Start a new display list
    Send_CMD(CLEAR_COLOR_RGB(0, 0, 0));                 //Determine the clear screen color
    Send_CMD(CLEAR(1, 1, 1));                           //Clear the screen and the current display list
    Cmd_Gradient(0, 100, 0x000000, 0, 272, 0x808080);   //Display black to gray gradient
    __delay_cycles(100);

    Send_CMD(COLOR_RGB(255, 255, 255));                 //Change color to white for text
    Cmd_Text(250, 40, 31, OPT_CENTER, "Select PLAY or RECORD:");
    __delay_cycles(100);

    Send_CMD(COLOR_RGB(255, 255, 255));                 //Change color to white for text
    Cmd_Text(40, 120, 31, OPT_CENTER, "1.");

    Send_CMD(COLOR_RGB(255, 255, 255));                 //Change color to white for text
    Cmd_Text(40, 180, 31, OPT_CENTER, "2.");

    Send_CMD(COLOR_RGB(34, 139, 34));                 //Change color to white for text
    Cmd_Text(130, 120, 31, OPT_CENTER, "PLAY");

    Send_CMD(COLOR_RGB(255, 0, 0));                 //Change color to white for text
    Cmd_Text(160, 180, 31, OPT_CENTER, "RECORD");

    Send_CMD(DISPLAY());                                //End the display list
    Send_CMD(CMD_SWAP);                                 //Swap commands into RAM
    __delay_cycles(100);
    UpdateFIFO();                                       // Trigger the CoProcessor to start processing the FIFO
}

void MakeScreen_PLAY_SelectTrack(){
    Send_CMD(CMD_DLSTART);                              //Start a new display list
    Send_CMD(CLEAR_COLOR_RGB(0, 0, 0));                 //Determine the clear screen color
    Send_CMD(CLEAR(1, 1, 1));                           //Clear the screen and the current display list
    Cmd_Gradient(0, 100, 0x000000, 0, 272, 0x808080);   //Display black to gray gradient
    __delay_cycles(100);

    Send_CMD(COLOR_RGB(255, 255, 255));                 //Change color to white for text
    Cmd_Text(140, 40, 31, OPT_CENTER, "Select Track:");
    __delay_cycles(100);

    Send_CMD(COLOR_RGB(255, 255, 255));                 //Change color to white for text
    Cmd_Text(40, 120, 31, OPT_CENTER, "1.");
    Cmd_Text(40, 170, 31, OPT_CENTER, "2.");
    Cmd_Text(40, 220, 31, OPT_CENTER, "3:");

    Send_CMD(COLOR_RGB(148, 0, 211));                   //Change color to dark orchid for text
    Cmd_Text(220, 120, 24, OPT_CENTER, "BAD GUY [CLAY K. SLIDER]");
    Cmd_Text(230, 170, 24, OPT_CENTER, "FREEFORM JAZZ [JAZZ GUY]");
    Cmd_Text(150, 220, 24, OPT_CENTER, "CUSTOM TRACK");

    Send_CMD(DISPLAY());                                //End the display list
    Send_CMD(CMD_SWAP);                                 //Swap commands into RAM
    __delay_cycles(100);
    UpdateFIFO();                                       // Trigger the CoProcessor to start processing the FIFO
}

void MakeScreen_PLAY_PlayTrack(int vol){
    Send_CMD(CMD_DLSTART);                              //Start a new display list
    Send_CMD(CLEAR_COLOR_RGB(0, 0, 0));                 //Determine the clear screen color
    Send_CMD(CLEAR(1, 1, 1));                           //Clear the screen and the current display list
    Cmd_Gradient(0, 100, 0x000000, 0, 272, 0x808080);   //Display black to gray gradient
    __delay_cycles(100);

    Send_CMD(COLOR_RGB(200, 200, 200));                 //Change color to violet for text
    Cmd_Text(DWIDTH / 2, DHEIGHT / 4, 31, OPT_CENTER, "Playing track...");
    Send_CMD(COLOR_RGB(0, 0, 0));                 //Change color to violet for text
    Cmd_Text(100, 210, 31, OPT_CENTER, "VOLUME");

    Send_CMD(COLOR_RGB(0, 250, 0));                     //Change color to green for slider
    Cmd_FGcolor(0x228B22);
    Cmd_BGcolor(0xC0C0C0);
    Cmd_Slider(200, 200, 250, 30, 0, vol, 17000);
    Send_CMD(DISPLAY());                                //End the display list
    Send_CMD(CMD_SWAP);                                 //Swap commands into RAM
    __delay_cycles(100);
    UpdateFIFO();                                       // Trigger the CoProcessor to start processing the FIFO
}


void MakeScreen_RECORD_SelectTrack(){
    Send_CMD(CMD_DLSTART);                              //Start a new display list
    Send_CMD(CLEAR_COLOR_RGB(0, 0, 0));                 //Determine the clear screen color
    Send_CMD(CLEAR(1, 1, 1));                           //Clear the screen and the current display list
    Cmd_Gradient(0, 100, 0x000000, 0, 272, 0x808080);   //Display black to gray gradient
    __delay_cycles(100);

    Send_CMD(COLOR_RGB(255, 255, 255));                 //Change color to white for text
    Cmd_Text(140, 40, 31, OPT_CENTER, "Select Track:");
    __delay_cycles(100);

    Send_CMD(COLOR_RGB(255, 255, 255));                 //Change color to white for text
    Cmd_Text(40, 120, 31, OPT_CENTER, "1.");
    Cmd_Text(40, 170, 31, OPT_CENTER, "2.");
    Cmd_Text(40, 220, 31, OPT_CENTER, "3:");

    Send_CMD(COLOR_RGB(148, 0, 211));                   //Change color to dark orchid for text
    Cmd_Text(220, 120, 24, OPT_CENTER, "BAD GUY [CLAY K. SLIDER]");
    Cmd_Text(230, 170, 24, OPT_CENTER, "FREEFORM JAZZ [JAZZ GUY]");
    Cmd_Text(150, 220, 24, OPT_CENTER, "CUSTOM TRACK");

    Send_CMD(DISPLAY());                                //End the display list
    Send_CMD(CMD_SWAP);                                 //Swap commands into RAM
    __delay_cycles(100);
    UpdateFIFO();                                       // Trigger the CoProcessor to start processing the FIFO
}

void MakeScreen_RECORD_RecordTrack(){
    Send_CMD(CMD_DLSTART);                              //Start a new display list
    Send_CMD(CLEAR_COLOR_RGB(0, 0, 0));                 //Determine the clear screen color
    Send_CMD(CLEAR(1, 1, 1));                           //Clear the screen and the current display list
    Cmd_Gradient(0, 100, 0x000000, 0, 272, 0x808080);   //Display black to gray gradient
    __delay_cycles(100);

    Send_CMD(COLOR_RGB(255, 0, 0));                 //Change color to white for text
    Cmd_Text(DWIDTH / 2, DHEIGHT / 2, 31, OPT_CENTER, "--RECORDING--");
    __delay_cycles(100);

    Send_CMD(DISPLAY());                                //End the display list
    Send_CMD(CMD_SWAP);                                 //Swap commands into RAM
    __delay_cycles(100);
    UpdateFIFO();                                       // Trigger the CoProcessor to start processing the FIFO
}

void MakeScreen_RECORD_Success(){
    Send_CMD(CMD_DLSTART);                              //Start a new display list
    Send_CMD(CLEAR_COLOR_RGB(0, 0, 0));                 //Determine the clear screen color
    Send_CMD(CLEAR(1, 1, 1));                           //Clear the screen and the current display list
    Cmd_Gradient(0, 100, 0x000000, 0, 272, 0x808080);   //Display black to gray gradient
    __delay_cycles(100);

    Send_CMD(COLOR_RGB(255, 255, 255));                 //Change color to white for text
    Cmd_Text(DWIDTH / 2, DHEIGHT / 2, 31, OPT_CENTER, "TRACK SAVED");
    __delay_cycles(100);


    Send_CMD(DISPLAY());                                //End the display list
    Send_CMD(CMD_SWAP);                                 //Swap commands into RAM
    __delay_cycles(100);
    UpdateFIFO();                                       // Trigger the CoProcessor to start processing the FIFO
}


