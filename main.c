//******************************************************************************
//  MSP-FET430P140 Demo - WDT, Toggle P3.4, Interval Overflow ISR, DCO SMCLK
//
//  Description: Toggle P3.4 using software timed by the WDT ISR. Toggle rate
//  is approximately 30ms based on default ~ 800khz DCO/SMCLK clock source
//  used in this example for the WDT.
//  ACLK= n/a, MCLK= SMCLK= default DCO~ 800k
//
//		  MSP430F149
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P3.4|-->LED
//
//  Dasheng
//  LiTian Electronic Inc.
//  Feb 2008
//  Built with IAR Embedded Workbench Version: 3.42A
//******************************************************************************
这是一个测试，分支操作的测试，好像还有分支合并的功能
#include  <msp430x14x.h>

void main(void)
{
  P6DIR |= BIT2;P6OUT |= BIT2;              //¹ØµçÆ½×ª»»
  WDTCTL = WDT_MDLY_32;                     // Set Watchdog Timer interval to ~30ms
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P2DIR |= BIT4;                            // Set P3.4 to output direction
   P2DIR |= BIT6;                            // Set P3.4 to output direction
   P2OUT ^= BIT6; 
    P2DIR |= BIT5;                            // Set P3.4 to output direction
   P2OUT |= BIT5; 
    P2DIR |= BIT7;                            // Set P3.4 to output direction
   P2OUT ^= BIT7; 
  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  P2OUT ^= BIT4;                            // Toggle P3.4 using exclusive-OR
}

