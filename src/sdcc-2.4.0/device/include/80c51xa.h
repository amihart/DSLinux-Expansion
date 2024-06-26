/*
 *	XA G3 SFR definitions
 *	Extracted directly from Philips documentation
 */

#ifndef	XA_H
#define	XA_H

sfr at 0x400 /*unsigned short*/ PSW; /* Program status word */
sfr at 0x400 PSWL; /* Program status word (low byte) */
sfr at 0x401 PSWH; /* Program status word (high byte) */
sfr at 0x402 PSW51; /* 80C51 compatible PSW */
sfr at 0x403 SSEL; /* Segment selection register */
sfr at 0x404 PCON; /* Power control register */
sfr at 0x410 TCON; /* Timer 0 and 1 control register */
sfr at 0x411 TSTAT; /* Timer 0 and 1 extended status */
sfr at 0x418 T2CON; /* Timer 2 control register */
sfr at 0x419 T2MOD; /* Timer 2 mode control */
sfr at 0x41F WDCON; /* Watchdog control register */
sfr at 0x420 S0CON; /* Serial port 0 control register */
sfr at 0x421 S0STAT; /* Serial port 0 extended status */
sfr at 0x424 S1CON; /* Serial port 1 control register */
sfr at 0x425 S1STAT; /* Serial port 1 extended status */
sfr at 0x426 IEL; /* Interrupt enable low byte */
sfr at 0x427 IEH; /* Interrupt enable high byte */
sfr at 0x42A SWR; /* Software Interrupt Request */
sfr at 0x430 P0; /* Port 0 */
sfr at 0x431 P1; /* Port 1 */
sfr at 0x432 P2; /* Port 2 */
sfr at 0x433 P3; /* Port3 */
sfr at 0x440 SCR; /* System configuration register */
sfr at 0x441 DS; /* Data segment */
sfr at 0x442 ES; /* Extra segment */
sfr at 0x443 CS; /* Code segment */
sfr at 0x450 TL0; /* Timer 0 low byte */
sfr at 0x451 TH0; /* Timer 0 high byte */
sfr at 0x452 TL1; /* Timer 1 low byte */
sfr at 0x453 TH1; /* Timer 1 high byte */
sfr at 0x454 RTL0; /* Timer 0 extended reload, low byte */
sfr at 0x455 RTH0; /* Timer 0 extended reload, high byte */
sfr at 0x456 RTL1; /* Timer 1 extended reload, low byte */
sfr at 0x457 RTH1; /* Timer 1 extended reload, high byte */
sfr at 0x458 TL2; /* Timer 2 low byte */
sfr at 0x459 TH2; /* Timer 2 high byte */
sfr at 0x45A T2CAPL; /* Timer 2 capture register, low byte */
sfr at 0x45B T2CAPH; /* Timer 2 capture register, high byte */
sfr at 0x45C TMOD; /* Timer 0 and 1 mode register */
sfr at 0x45D WFEED1; /* Watchdog feed 1 */
sfr at 0x45E WFEED2; /* Watchdog feed 2 */
sfr at 0x45F WDL; /* Watchdog timer reload */
sfr at 0x460 S0BUF; /* Serial port 0 buffer register */
sfr at 0x461 S0ADDR; /* Serial port 0 address register */
sfr at 0x462 S0ADEN; /* Serial port 0 address enable register */
sfr at 0x464 S1BUF; /* Serial port 1 buffer register */
sfr at 0x465 S1ADDR; /* Serial port 1 address register */
sfr at 0x466 S1ADEN; /* Serial port 1 address enable register */
sfr at 0x468 BTRL; /* Bus timing register high byte */
sfr at 0x469 BTRH; /* Bus timing register low byte */
sfr at 0x46A BCR; /* Bus configuration register */
sfr at 0x470 P0CFGA; /* Port 0 configuration A */
sfr at 0x471 P1CFGA; /* Port 1 configuration A */
sfr at 0x472 P2CFGA; /* Port 2 configuration A */
sfr at 0x473 P3CFGA; /* Port 3 configuration A */
sfr at 0x47A SWE; /* Software Interrupt Enable */
sfr at 0x4A0 IPA0; /* Interrupt priority 0 */
sfr at 0x4A1 IPA1; /* Interrupt priority 1 */
sfr at 0x4A2 IPA2; /* Interrupt priority 2 */
sfr at 0x4A4 IPA4; /* Interrupt priority 4 */
sfr at 0x4A5 IPA5; /* Interrupt priority 5 */
sfr at 0x4F0 P0CFGB; /* Port 0 configuration B */
sfr at 0x4F1 P1CFGB; /* Port 1 configuration B */
sfr at 0x4F2 P2CFGB; /* Port 2 configuration B */
sfr at 0x4F3 P3CFGB; /* Port 3 configuration B */

sbit  at 0x33B ETI1; /* TX interrupt enable 1 */
sbit  at 0x33A ERI1; /* RX interrupt enable 1 */
sbit  at 0x339 ETI0; /* TX interrupt enable 0 */
sbit  at 0x338 ERI0; /* RX interrupt enable 0 */
sbit  at 0x337 EA; /* global int. enable */
sbit  at 0x334 ET2; /* timer 2 interrupt */
sbit  at 0x333 ET1; /* timer 1 interrupt */
sbit  at 0x332 EX1; /* external interrupt 1 */
sbit  at 0x331 ET0; /* timer 0 interrupt */
sbit  at 0x330 EX0; /* external interrupt 0 */
sbit  at 0x221 PD; /* power down */
sbit  at 0x220 IDL;
sbit  at 0x20F SM;
sbit  at 0x20E TM;
sbit  at 0x20D RS1;
sbit  at 0x20C RS0;
sbit  at 0x20B IM3;
sbit  at 0x20A IM2;
sbit  at 0x209 IM1;
sbit  at 0x208 IM0;
sbit  at 0x307 S0M0;
sbit  at 0x306 S0M1;
sbit  at 0x305 S0M2;
sbit  at 0x304 R0EN;
sbit  at 0x303 T0B8;
sbit  at 0x302 R0B8;
sbit  at 0x301 TI0; /* serial port 0 tx ready */
sbit  at 0x300 RI0; /* serial port 0 rx ready */
sbit  at 0x30B FE0;
sbit  at 0x30A BR0;
sbit  at 0x309 OE0;
sbit  at 0x308 STINT0;
sbit  at 0x327 S1M0;
sbit  at 0x326 S1M1;
sbit  at 0x325 S1M2;
sbit  at 0x324 R1EN;
sbit  at 0x323 T1B8;
sbit  at 0x322 R1B8;
sbit  at 0x321 TI1; /* serial port 0 tx ready */
sbit  at 0x320 RI1; /* serial port 0 rx ready */
sbit  at 0x32B FE1;
sbit  at 0x32A BR1;
sbit  at 0x329 OE1;
sbit  at 0x328 STINT1;
sbit  at 0x356 SWR7;
sbit  at 0x355 SWR6;
sbit  at 0x354 SWR5;
sbit  at 0x353 SWR4;
sbit  at 0x352 SWR3;
sbit  at 0x351 SWR2;
sbit  at 0x350 SWR1;
sbit  at 0x2C7 TF2;
sbit  at 0x2C6 EXF2;
sbit  at 0x2C5 RCLK0;
sbit  at 0x2C4 TCLK0;
sbit  at 0x2CD RCLK1;
sbit  at 0x2CC TCLK1;
sbit  at 0x2C3 EXEN2;
sbit  at 0x2C2 TR2;
sbit  at 0x2C1 CT2;
sbit  at 0x2C0 CPRL2;
sbit  at 0x2C9 T2OE;
sbit  at 0x2C8 DCEN;
sbit  at 0x287 TF1;
sbit  at 0x286 TR1;
sbit  at 0x285 TF0;
sbit  at 0x284 TR0;
sbit  at 0x283 IE1;
sbit  at 0x282 IT1;
sbit  at 0x281 IE0;
sbit  at 0x280 IT0;
sbit  at 0x28A T1OE;
sbit  at 0x288 T0OE;
sbit  at 0x2FF PRE2;
sbit  at 0x2FE PRE1;
sbit  at 0x2FD PRE0;
sbit  at 0x2FA WDRUN;
sbit  at 0x2F9 WDTOF;
sbit  at 0x2F8 WDMOD;
sbit  at 0x388 WR1;
sbit  at 0x38F T2EX;
sbit  at 0x38C RXD1;
sbit  at 0x38D TXD1;
sbit  at 0x398 RXD0;
sbit  at 0x399 TXD0;
sbit  at 0x39A INT0;
sbit  at 0x39B INT1;
sbit  at 0x39C T0;
sbit  at 0x39D T1;
sbit  at 0x39E WR;
sbit  at 0x39F RD;

/*
 * Interrupt stuff
 */


/* Vectors */

#define IV_BRKPT 0x04 /* breakpoint vector */
#define IV_TRACE 0x08 /* Trace mode bit set */
#define IV_STKOVER 0x0C /* stack overflow */
#define IV_DIVZERO 0x10 /* divide by zero */
#define IV_IRET 0x14 /* user mode IRET */

#define IV_EX0 0x80
#define IV_T0 0x84
#define IV_EX1 0x88
#define IV_T1 0x8C
#define IV_T2 0x90
#define IV_RI0 0xA0
#define IV_TI0 0xA4
#define IV_RI1 0xA8
#define IV_TI1 0xAC
#define IV_SWI1 0x100 /* software interrupts */
#define IV_SWI2 0x104
#define IV_SWI3 0x108
#define IV_SWI4 0x10C
#define IV_SWI5 0x110
#define IV_SWI6 0x114
#define IV_SWI7 0x118

/* PSW Values for interrupt vectors */

#define IV_PSW 0x8F00 /* System mode, high priority, bank 0 */

#define IV_SYSTEM 0x8000

#define IV_PRI00 0x0000 /* priorities 0 - 15 */
#define IV_PRI01 0x0100
#define IV_PRI02 0x0200
#define IV_PRI03 0x0300
#define IV_PRI04 0x0400
#define IV_PRI05 0x0500
#define IV_PRI06 0x0600
#define IV_PRI07 0x0700
#define IV_PRI08 0x0800
#define IV_PRI09 0x0900
#define IV_PRI10 0x0A00
#define IV_PRI11 0x0B00
#define IV_PRI12 0x0C00
#define IV_PRI13 0x0D00
#define IV_PRI14 0x0E00
#define IV_PRI15 0x0F00

#define IV_BANK0 0x0000
#define IV_BANK1 0x1000
#define IV_BANK2 0x2000
#define IV_BANK3 0x3000

#endif /* XA_H */
