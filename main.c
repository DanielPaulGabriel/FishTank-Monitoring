/*
 * File:   main.c
 * Author: Daniel
 *
 * Created on 26 June, 2023, 1:35 PM
 */
#include <xc.h>
#include "config.h" 
#define SPKR PORTBbits.RB3
void initSysPins(void);
void initSysExtInt(void);
void initLCD(void);
void initADC(void);
void initSysExtInt(void);
void lcdWriteDspData(char x);
void lcdCtrl_ClearDisplay(void);
void lcdCtrl_ClearSecondRow(void);
void lcdCtrl_SetPos(char row, char col);
unsigned int adc_GetConversionTemp(void);
unsigned int adc_GetConversionOxygen(void);
unsigned int adc_GetConversionLight(void);
void adc_DispT(void);
void adc_DispO(void);
void adc_DispL(void);


void main(void) {
    unsigned int resultT;
    unsigned int resultO;
    unsigned int resultL;
    unsigned int prevResult = 0;
    unsigned int i;
    unsigned int cnt;
    initSysPins();
    initADC();
    initLCD();
    
    while(1){
        // Check if the button for "Temperature" is pressed
        if (PORTBbits.RB2 == 0){
            resultT = adc_GetConversionTemp();
            lcdCtrl_ClearDisplay();
            char messageS[] = "Temperature";
            lcdCtrl_SetPos(1,1);
            for(i = 0;messageS[i]!=0;i++){
            lcdWriteDspData(messageS[i]);
            }
            adc_DispT();
        }
            // Check if the button for "Oxygen" is pressed
            else if (PORTBbits.RB1 == 0){
            resultO = adc_GetConversionOxygen();
            lcdCtrl_ClearDisplay();
            char messageS[] = "Oxygen";
            lcdCtrl_SetPos(1,1);
            for(i = 0;messageS[i]!=0;i++){
            lcdWriteDspData(messageS[i]);
            }
            adc_DispO();
        }
            // Check if the button for "Light" is pressed
            else if(PORTBbits.RB4 == 0){
            lcdCtrl_ClearDisplay();
            char messageS[] = "Light";
            lcdCtrl_SetPos(1,1);
            for(i = 0;messageS[i]!=0;i++){
            lcdWriteDspData(messageS[i]);
            }
            adc_DispL();
            }
        
            __delay_ms(500);     // Delay before the next iteration
                 
    }
    
                 
        
                
    
    //return;
}
void initSysPins(void){     // Function to initialize system pins
    ANSELA = 0b00001111;
    ANSELB = 0b00000000;
    TRISA = 0b11111111;//ra0 0
    TRISB = 0b11110111;
    ANSELC = 0b00000000;
    TRISC = 0b11111111;  
    ANSELD = 0b00000000;
    TRISD = 0b00001111;
    ANSELE = 0b00000000;
    TRISE = 0b11111100; 
    
}
