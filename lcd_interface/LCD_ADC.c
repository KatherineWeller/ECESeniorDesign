/*
 * LCD_ADC.c
 *
 *  Created on: Apr 8, 2020
 *      Author: weller
 */

#include <Include/adc14.h>
#include <msp432.h>
#include "driverlib.h"

void Init_ADC();

void Init_ADC(){
    //Set GPIO
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN5, GPIO_TERTIARY_MODULE_FUNCTION);

    //Configure ADC14
    ADC14_disableModule();
    ADC14_initModule(ADC_CLOCKSOURCE_SMCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1,0);
    ADC14_setSampleHoldTrigger(ADC_TRIGGER_ADCSC, false);
    //ADC14_setSampleHoldTime(ADC_PULSE_WIDTH_64, ADC_PULSE_WIDTH_64);

    ADC14_configureSingleSampleMode(ADC_MEM0, true);
    ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A1, false);
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
    ADC14_setResolution(ADC_14BIT);
    ADC14->IER0 |= ADC14_IER0_IE0;              //Enable ADC conversion complete interrupt
    ADC14_enableModule();
}

void ADC14IsrHandler(void){
    int volume = ADC14_getResult(ADC_MEM0);
}


