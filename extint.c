/*
 * File:   extint.c
 * Author: Daniel
 *
 * Created on 3 July, 2023, 1:00 PM
 */


#include <xc.h>
#include "config.h"

void initSysExtInt(void){
    INTCONbits.GIE = 0;
    PIR0bits.INTF = 0;
    INTPPS = 0x09;
    INTCONbits.INTEDG = 1;
    PIE0bits.INTE = 1;
    INTCONbits.GIE = 1;
}
