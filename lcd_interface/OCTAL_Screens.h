/*
 * OCTAL_Screens.h
 *
 *  Created on: Mar 15, 2020
 *      Author: kattw
 */

#ifndef OCTAL_SCREENS_H_
#define OCTAL_SCREENS_H_

void InitLEDGPio();

void MakeScreen_Loading();
void MakeScreen_OctalLogo();
void MakeScreen_OctalLogo_xStart();
void MakeScreen_Tutorial_Page1();
void MakeScreen_Tutorial_Page2();
void MakeScreen_Prompt_PLAY_RECORD();
void MakeScreen_PLAY_SelectTrack();
void MakeScreen_PLAY_PlayTrack();
void MakeScreen_RECORD_SelectTrack();
void MakeScreen_RECORD_RecordTrack();
void MakeScreen_RECORD_Success();

uint32_t Load_RAWH(uint32_t BASE_BIT_ADDR, uint8_t rawh[], uint32_t size);

#endif /* OCTAL_SCREENS_H_ */
