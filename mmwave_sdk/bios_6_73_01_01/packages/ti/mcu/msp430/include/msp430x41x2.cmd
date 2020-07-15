/******************************************************************************/
/* Legacy Linker Command File                                                 */
/* Not recommended for use in new projects.                                   */
/* Please use the device specific cmd file                                    */
/******************************************************************************/

/* ============================================================================ */
/* Copyright (c) 2014, Texas Instruments Incorporated                           */
/*  All rights reserved.                                                        */
/*                                                                              */
/*  Redistribution and use in source and binary forms, with or without          */
/*  modification, are permitted provided that the following conditions          */
/*  are met:                                                                    */
/*                                                                              */
/*  *  Redistributions of source code must retain the above copyright           */
/*     notice, this list of conditions and the following disclaimer.            */
/*                                                                              */
/*  *  Redistributions in binary form must reproduce the above copyright        */
/*     notice, this list of conditions and the following disclaimer in the      */
/*     documentation and/or other materials provided with the distribution.     */
/*                                                                              */
/*  *  Neither the name of Texas Instruments Incorporated nor the names of      */
/*     its contributors may be used to endorse or promote products derived      */
/*     from this software without specific prior written permission.            */
/*                                                                              */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" */
/*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,       */
/*  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      */
/*  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR            */
/*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,       */
/*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,         */
/*  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; */
/*  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,    */
/*  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR     */
/*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,              */
/*  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                          */
/* ============================================================================ */

/******************************************************************************/
/* msp430f4152.cmd                                                            */
/*    - Linker Command File for defintions in the header file                 */
/*    Please do not change !                                                  */
/*                                                                            */
/******************************************************************************/
/* Version: 1.121                                                             */
/******************************************************************************/


/************************************************************
* STANDARD BITS
************************************************************/
/************************************************************
* STATUS REGISTER BITS
************************************************************/
/************************************************************
* PERIPHERAL FILE MAP
************************************************************/
/************************************************************
* SPECIAL FUNCTION REGISTER ADDRESSES + CONTROL BITS
************************************************************/
IE1                = 0x0000;
IFG1               = 0x0002;
IE2                = 0x0001;
IFG2               = 0x0003;
/************************************************************
* ADC10
************************************************************/
ADC10DTC0          = 0x0048;
ADC10DTC1          = 0x0049;
ADC10AE0           = 0x004A;
ADC10AE1           = 0x004B;
ADC10CTL0          = 0x01B0;
ADC10CTL1          = 0x01B2;
ADC10MEM           = 0x01B4;
ADC10SA            = 0x01BC;
/************************************************************
* BASIC TIMER with Real Time Clock
************************************************************/
BTCTL              = 0x0040;
RTCCTL             = 0x0041;
RTCNT1             = 0x0042;
RTCNT2             = 0x0043;
RTCNT3             = 0x0044;
RTCNT4             = 0x0045;
BTCNT1             = 0x0046;
BTCNT2             = 0x0047;
RTCDAY             = 0x004C;
RTCMON             = 0x004D;
RTCYEARL           = 0x004E;
RTCYEARH           = 0x004F;
RTCTL              = 0x0040;
RTCTIM0            = 0x0042;
RTCTIM1            = 0x0044;
BTCNT12            = 0x0046;
RTCDATE            = 0x004C;
RTCYEAR            = 0x004E;
/************************************************************
* Comparator A
************************************************************/
CACTL1             = 0x0059;
CACTL2             = 0x005A;
CAPD               = 0x005B;
/*************************************************************
* Flash Memory
*************************************************************/
FCTL1              = 0x0128;
FCTL2              = 0x012A;
FCTL3              = 0x012C;
/************************************************************
* SYSTEM CLOCK, FLL+
************************************************************/
SCFI0              = 0x0050;
SCFI1              = 0x0051;
SCFQCTL            = 0x0052;
FLL_CTL0           = 0x0053;
FLL_CTL1           = 0x0054;
FLL_CTL2           = 0x0055;
/************************************************************
* LCD_A
************************************************************/
LCDACTL            = 0x0090;
LCDAPCTL0          = 0x00AC;
LCDAPCTL1          = 0x00AD;
LCDAVCTL0          = 0x00AE;
LCDAVCTL1          = 0x00AF;
LCDM1              = 0x0091;
LCDM2              = 0x0092;
LCDM3              = 0x0093;
LCDM4              = 0x0094;
LCDM5              = 0x0095;
LCDM6              = 0x0096;
LCDM7              = 0x0097;
LCDM8              = 0x0098;
LCDM9              = 0x0099;
LCDM10             = 0x009A;
LCDM11             = 0x009B;
LCDM12             = 0x009C;
LCDM13             = 0x009D;
LCDM14             = 0x009E;
LCDM15             = 0x009F;
LCDM16             = 0x00A0;
LCDM17             = 0x00A1;
LCDM18             = 0x00A2;
LCDM19             = 0x00A3;
LCDM20             = 0x00A4;
/************************************************************
* DIGITAL I/O Port1/2
************************************************************/
P1IN               = 0x0020;
P1OUT              = 0x0021;
P1DIR              = 0x0022;
P1IFG              = 0x0023;
P1IES              = 0x0024;
P1IE               = 0x0025;
P1SEL              = 0x0026;
P2IN               = 0x0028;
P2OUT              = 0x0029;
P2DIR              = 0x002A;
P2IFG              = 0x002B;
P2IES              = 0x002C;
P2IE               = 0x002D;
P2SEL              = 0x002E;
/************************************************************
* DIGITAL I/O Port3/4
************************************************************/
P3IN               = 0x0018;
P3OUT              = 0x0019;
P3DIR              = 0x001A;
P3SEL              = 0x001B;
P4IN               = 0x001C;
P4OUT              = 0x001D;
P4DIR              = 0x001E;
P4SEL              = 0x001F;
/************************************************************
* DIGITAL I/O Port5/6
************************************************************/
P5IN               = 0x0030;
P5OUT              = 0x0031;
P5DIR              = 0x0032;
P5SEL              = 0x0033;
P6IN               = 0x0034;
P6OUT              = 0x0035;
P6DIR              = 0x0036;
P6SEL              = 0x0037;
/************************************************************
* DIGITAL I/O Port7
************************************************************/
P7IN               = 0x0038;
P7OUT              = 0x0039;
P7DIR              = 0x003A;
P7SEL              = 0x003B;
/************************************************************
* Brown-Out, Supply Voltage Supervision (SVS)
************************************************************/
SVSCTL             = 0x0056;
/************************************************************
* Timer0_A3
************************************************************/
TA0IV              = 0x012E;
TA0CTL             = 0x0160;
TA0CCTL0           = 0x0162;
TA0CCTL1           = 0x0164;
TA0CCTL2           = 0x0166;
TA0R               = 0x0170;
TA0CCR0            = 0x0172;
TA0CCR1            = 0x0174;
TA0CCR2            = 0x0176;
/************************************************************
* Timer1_A5
************************************************************/
TA1IV              = 0x011E;
TA1CTL             = 0x0180;
TA1CCTL0           = 0x0182;
TA1CCTL1           = 0x0184;
TA1CCTL2           = 0x0186;
TA1CCTL3           = 0x0188;
TA1CCTL4           = 0x018A;
TA1R               = 0x0190;
TA1CCR0            = 0x0192;
TA1CCR1            = 0x0194;
TA1CCR2            = 0x0196;
TA1CCR3            = 0x0198;
TA1CCR4            = 0x019A;
/************************************************************
* USCI
************************************************************/
UCA0CTL0           = 0x0060;
UCA0CTL1           = 0x0061;
UCA0BR0            = 0x0062;
UCA0BR1            = 0x0063;
UCA0MCTL           = 0x0064;
UCA0STAT           = 0x0065;
UCA0RXBUF          = 0x0066;
UCA0TXBUF          = 0x0067;
UCA0ABCTL          = 0x005D;
UCA0IRTCTL         = 0x005E;
UCA0IRRCTL         = 0x005F;
UCB0CTL0           = 0x0068;
UCB0CTL1           = 0x0069;
UCB0BR0            = 0x006A;
UCB0BR1            = 0x006B;
UCB0I2CIE          = 0x006C;
UCB0STAT           = 0x006D;
UCB0RXBUF          = 0x006E;
UCB0TXBUF          = 0x006F;
UCB0I2COA          = 0x0118;
UCB0I2CSA          = 0x011A;
/************************************************************
* WATCHDOG TIMER
************************************************************/
WDTCTL             = 0x0120;
/************************************************************
* Interrupt Vectors (offset from 0xFFE0)
************************************************************/
/************************************************************
* End of Modules
************************************************************/
