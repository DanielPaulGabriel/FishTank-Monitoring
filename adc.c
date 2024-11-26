    /*
 * File:   adc.c
 * Author: Daniel
 *
 * Created on 26 June, 2023, 1:58 PM
 */


#include <xc.h>
#include "config.h"

void initADC(void){
    ADREF = 0b00000000;
    ADCLK = 0b00000011;
    ADACQ = 0b00000000;
    ADCON0 = 0b10000100;
}
unsigned int adc_GetConversionTemp(void){
    unsigned int resultT;
    ADPCH = 0b00000010; // 0b00000010 on proj board
    __delay_us(2);
    ADCON0bits.ADGO = 1;
    while(ADCON0bits.ADGO==1)
    resultT = ADRESH*256+ADRESL;
    return(resultT);
    
}
unsigned int adc_GetConversionLight(void){
    unsigned int resultL;
    ADPCH = 0b00000001;// 0b00000001
    __delay_us(2);
    ADCON0bits.ADGO = 1;
    while(ADCON0bits.ADGO==1)
    resultL = ADRESH*256+ADRESL;
    return(resultL);
    
}
unsigned int adc_GetConversionOxygen(void){
    unsigned int resultO;
    ADPCH = 0b00000011; // 0b00000011
    __delay_us(2);
    ADCON0bits.ADGO = 1;
    while(ADCON0bits.ADGO==1)
    resultO = ADRESH*256+ADRESL;
    return(resultO);
    
}
void adc_DispL(void) {
    void lcdCtrl_ClearDisplay(void);
    void lcdWriteDspData(char x);
    void lcdCtrl_ClearSecondRow(void);
    void lcdCtrl_SetPos(char row, char col);
    unsigned int resultL;
    unsigned int prevResult = 0;
    char message1[] = "VERYLOW";
    char message2[] = "LOW";
    char message3[] = "HIGH";
    char message4[] = "VERYHIGH";
    int i;
    int cnt;

    resultL = adc_GetConversionLight();  // Read the ADC value
    unsigned int dividedValue = resultL * 0.14;  // Calculate divided value 0.0316

    if (resultL != prevResult) {
        prevResult = resultL;
        lcdCtrl_ClearSecondRow();
        lcdCtrl_SetPos(2, 1);

        if (resultL < 10) {  // Check if the result is "VERYLOW"
            lcdCtrl_ClearSecondRow();
            lcdCtrl_SetPos(2, 1);
            for (i = 0; message1[i] != 0; i++) {
                lcdWriteDspData(message1[i]);
            }
            lcdWriteDspData(' ');  // Add a space for separation

            // Convert each digit to character and display
            lcdWriteDspData((dividedValue / 100) + '0');
            lcdWriteDspData(((dividedValue / 10) % 10) + '0');
            lcdWriteDspData((dividedValue % 10) + '0');
            lcdWriteDspData('L');
            for (cnt = 0; cnt < 1000; cnt++) {  // Sound the Speaker
                LATAbits.LATA1 = ~LATAbits.LATA1;
                PORTBbits.RB3 = 1;
                __delay_us(200);
                PORTBbits.RB3 = 0;
                __delay_us(200);
            }
            LATAbits.LATA1 = 0;
        } else if (resultL < 100 && resultL > 10) {  // Check if the result is "LOW"
            lcdCtrl_ClearSecondRow();
            lcdCtrl_SetPos(2, 1);
            for (i = 0; message2[i] != 0; i++) {
                lcdWriteDspData(message2[i]);
            }
            lcdWriteDspData(' ');  // Add a space for separation

            // Convert each digit to character and display
            
            lcdWriteDspData(((dividedValue / 10) % 10) + '0');
            lcdWriteDspData((dividedValue % 10) + '0');
            lcdWriteDspData('L');
        } else if (resultL < 1000 && resultL > 100) {  // Check if the result is "HIGH"
            lcdCtrl_ClearSecondRow();
            lcdCtrl_SetPos(2, 1);
            for (i = 0; message3[i] != 0; i++) {
                lcdWriteDspData(message3[i]);
            }
            lcdWriteDspData(' ');  // Add a space for separation

            // Convert each digit to character and display
            
            lcdWriteDspData(((dividedValue / 10) % 10) + '0');
            lcdWriteDspData((dividedValue % 10) + '0');
            lcdWriteDspData('L');
        } else {
            lcdCtrl_ClearSecondRow();
            lcdCtrl_SetPos(2, 1);
            for (i = 0; message4[i] != 0; i++) {
                lcdWriteDspData(message4[i]);
            }
            lcdWriteDspData(' ');  // Add a space for separation

            // Convert each digit to character and display
            
            lcdWriteDspData(((dividedValue / 10) % 10) + '0');
            lcdWriteDspData((dividedValue % 10) + '0');
            lcdWriteDspData('L');
        }
    }

    __delay_ms(500);
}
void adc_DispO(void) {
    void lcdCtrl_ClearDisplay(void);
    void lcdWriteDspData(char x);
    void lcdCtrl_ClearSecondRow(void);
    void lcdCtrl_SetPos(char row, char col);
    unsigned int resultO;
    unsigned int prevResult = 0;
    char message1[] = "VERYLOW";
    char message2[] = "LOW";
    char message3[] = "HIGH";
    char message4[] = "VERYHIGH";
    int i;
    int cnt;

    resultO = adc_GetConversionOxygen();  // Read the ADC value
    unsigned int dividedValue = resultO * 0.02;  // Calculate divided value

    if (resultO != prevResult) {
        prevResult = resultO;
        lcdCtrl_ClearSecondRow();
        lcdCtrl_SetPos(2, 1);

        if (resultO < 10) {  // Check if the result is "VERYLOW"
            lcdCtrl_ClearSecondRow();
            lcdCtrl_SetPos(2, 1);
            for (i = 0; message1[i] != 0; i++) {
                lcdWriteDspData(message1[i]);
            }
            lcdWriteDspData(' ');  // Add a space for separation

            // Convert each digit to character and display
            
            lcdWriteDspData((dividedValue % 10) + '0');
            lcdWriteDspData('p');
            lcdWriteDspData('p');
            lcdWriteDspData('m');
            for (cnt = 0; cnt < 1000; cnt++) {  // Sound the Speaker
                LATAbits.LATA1 = ~LATAbits.LATA1;
                PORTBbits.RB3 = 1;
                __delay_us(200);
                PORTBbits.RB3 = 0;
                __delay_us(200);
            }
            LATAbits.LATA1 = 0;
        } else if (resultO < 100 && resultO > 10) {  // Check if the result is "LOW"
            lcdCtrl_ClearSecondRow();
            lcdCtrl_SetPos(2, 1);
            for (i = 0; message2[i] != 0; i++) {
                lcdWriteDspData(message2[i]);
            }
            lcdWriteDspData(' ');  // Add a space for separation

            // Convert each digit to character and display
            
            lcdWriteDspData((dividedValue % 10) + '0');
            lcdWriteDspData('p');
            lcdWriteDspData('p');
            lcdWriteDspData('m');
        } else if (resultO < 1000 && resultO > 100) {  // Check if the result is "HIGH"
            lcdCtrl_ClearSecondRow();
            lcdCtrl_SetPos(2, 1);
            for (i = 0; message3[i] != 0; i++) {
                lcdWriteDspData(message3[i]);
            }
            lcdWriteDspData(' ');  // Add a space for separation

            // Convert each digit to character and display
            
            lcdWriteDspData((dividedValue % 10) + '0');
            lcdWriteDspData('p');
            lcdWriteDspData('p');
            lcdWriteDspData('m');
        } else {
            lcdCtrl_ClearSecondRow();
            lcdCtrl_SetPos(2, 1);
            for (i = 0; message4[i] != 0; i++) {
                lcdWriteDspData(message4[i]);
            }
            lcdWriteDspData(' ');  // Add a space for separation

            // Convert each digit to character and display
            
            lcdWriteDspData((dividedValue % 10) + '0');
            lcdWriteDspData('p');
            lcdWriteDspData('p');
            lcdWriteDspData('m');
        }
    }

    __delay_ms(500);
}
void adc_DispT(void) {
    void lcdCtrl_ClearDisplay(void);
    void lcdWriteDspData(char x);
    void lcdCtrl_ClearSecondRow(void);
    void lcdCtrl_SetPos(char row, char col);
    unsigned int resultT;
    unsigned int prevResult = 0;
    char message1[] = "VERYLOW";
    char message2[] = "LOW";
    char message3[] = "HIGH";
    char message4[] = "VERYHIGH";
    int i;
    int cnt;

    resultT = adc_GetConversionTemp();  // Read the ADC value
    unsigned int dividedValue = resultT /6;  // Calculate divided value

    if (resultT != prevResult) {
        prevResult = resultT;
        lcdCtrl_ClearSecondRow();
        lcdCtrl_SetPos(2, 1);

        if (resultT < 10) {  // Check if the result is "VERYLOW"
            lcdCtrl_ClearSecondRow();
            lcdCtrl_SetPos(2, 1);
            for (i = 0; message1[i] != 0; i++) {
                lcdWriteDspData(message1[i]);
            }
            lcdWriteDspData(' ');  // Add a space for separation

            // Convert each digit to character and display
            lcdWriteDspData(((dividedValue / 100) % 10) + '0');
            lcdWriteDspData(((dividedValue / 10) % 10) + '0');
            lcdWriteDspData((dividedValue % 10) + '0');
            
            for (cnt = 0; cnt < 1000; cnt++) {  // Sound the Speaker
                LATAbits.LATA1 = ~LATAbits.LATA1;
                PORTBbits.RB3 = 1;
                __delay_us(200);
                PORTBbits.RB3 = 0;
                __delay_us(200);
            }
            LATAbits.LATA1 = 0;
        } else if (resultT < 100 && resultT > 10) {  // Check if the result is "LOW"
            lcdCtrl_ClearSecondRow();
            lcdCtrl_SetPos(2, 1);
            for (i = 0; message2[i] != 0; i++) {
                lcdWriteDspData(message2[i]);
            }
            lcdWriteDspData(' ');  // Add a space for separation

            // Convert each digit to character and display
            lcdWriteDspData(((dividedValue / 100) % 10) + '0');
            lcdWriteDspData(((dividedValue / 10) % 10) + '0');
            lcdWriteDspData((dividedValue % 10) + '0');
        } else if (resultT < 1000 && resultT > 100) {  // Check if the result is "HIGH"
            lcdCtrl_ClearSecondRow();
            lcdCtrl_SetPos(2, 1);
            for (i = 0; message3[i] != 0; i++) {
                lcdWriteDspData(message3[i]);
            }
            lcdWriteDspData(' ');  // Add a space for separation

            // Convert each digit to character and display
                    
            lcdWriteDspData(((dividedValue / 100) % 10) + '0');    
            lcdWriteDspData(((dividedValue / 10) % 10) + '0');     
            lcdWriteDspData((dividedValue % 10) + '0');
            lcdWriteDspData('.');
            lcdWriteDspData('0');
            lcdWriteDspData('C');

        } else {
            lcdCtrl_ClearSecondRow();
            lcdCtrl_SetPos(2, 1);
            for (i = 0; message4[i] != 0; i++) {
                lcdWriteDspData(message4[i]);
            }
            lcdWriteDspData(' ');  // Add a space for separation

            // Convert each digit to character and display
            lcdWriteDspData(((dividedValue / 100) % 10) + '0');
            lcdWriteDspData(((dividedValue / 10) % 10) + '0');
            lcdWriteDspData((dividedValue % 10) + '0');
            for (cnt = 0; cnt < 1000; cnt++) {  // Sound the Speaker
                LATAbits.LATA1 = ~LATAbits.LATA1;
                PORTBbits.RB3 = 1;
                __delay_us(200);
                PORTBbits.RB3 = 0;
                __delay_us(200);
            }
        }
    }

    __delay_ms(500);
}

//Test
//lcdWriteDspData(' ');  // Add a space for separation

            // Convert each digit to character and display
           // lcdWriteDspData((dividedValue / 100) + '0');
           // lcdWriteDspData(((dividedValue / 10) % 10) + '0');
           // lcdWriteDspData((dividedValue % 10) + '0');
    

