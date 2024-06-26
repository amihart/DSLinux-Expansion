/*-------------------------------------------------------------------------
  Register Declarations for Motorola MC68HC908JB8
  
  Copyright (c) 2004, Bjorn Bringert <bjorn@bringert.net>

  Based on mc68hc908qy.h,
   Written By - Erik Petrich
    epetrich@users.sourceforge.net (2003)
    
   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
   
   In other words, you are welcome to use, share and improve this program.
   You are forbidden to forbid anyone else to use, share and improve
   what you give them.   Help stamp out software-hoarding!  
-------------------------------------------------------------------------*/

#ifndef MC68HC908JB8_H
#define MC68HC908JB8_H

#ifndef UINT8
 #define UINT8 unsigned char
#endif
#ifndef UINT16
 #define UINT16 unsigned int
#endif
#ifndef VOLDATA
 #define VOLDATA volatile data
#endif
#ifndef VOLXDATA
 #define VOLXDATA volatile xdata
#endif

struct _hc08_bits
{
  unsigned int bit0:1;
  unsigned int bit1:1;
  unsigned int bit2:1;
  unsigned int bit3:1;
  unsigned int bit4:1;
  unsigned int bit5:1;
  unsigned int bit6:1;
  unsigned int bit7:1;
};
  

VOLDATA UINT8 at 0x00 PTA;     /* Port A Data Register */
  #define PTA0 ((struct _hc08_bits *)(&PTA))->bit0
  #define PTA1 ((struct _hc08_bits *)(&PTA))->bit1
  #define PTA2 ((struct _hc08_bits *)(&PTA))->bit2
  #define PTA3 ((struct _hc08_bits *)(&PTA))->bit3
  #define PTA4 ((struct _hc08_bits *)(&PTA))->bit4
  #define PTA5 ((struct _hc08_bits *)(&PTA))->bit5
  #define AWUL ((struct _hc08_bits *)(&PTA))->bit6
  
VOLDATA UINT8 at 0x01 PTB;     /* Port B Data Register */
  #define PTB0 ((struct _hc08_bits *)(&PTB))->bit0
  #define PTB1 ((struct _hc08_bits *)(&PTB))->bit1
  #define PTB2 ((struct _hc08_bits *)(&PTB))->bit2
  #define PTB3 ((struct _hc08_bits *)(&PTB))->bit3
  #define PTB4 ((struct _hc08_bits *)(&PTB))->bit4
  #define PTB5 ((struct _hc08_bits *)(&PTB))->bit5
  #define PTB6 ((struct _hc08_bits *)(&PTB))->bit6
  #define PTB7 ((struct _hc08_bits *)(&PTB))->bit7

VOLDATA UINT8 at 0x02 PTC;     /* Port C Data Register */
  #define PTC0 ((struct _hc08_bits *)(&PTC))->bit0
  #define PTC1 ((struct _hc08_bits *)(&PTC))->bit1
  #define PTC2 ((struct _hc08_bits *)(&PTC))->bit2
  #define PTC3 ((struct _hc08_bits *)(&PTC))->bit3
  #define PTC4 ((struct _hc08_bits *)(&PTC))->bit4
  #define PTC5 ((struct _hc08_bits *)(&PTC))->bit5
  #define PTC6 ((struct _hc08_bits *)(&PTC))->bit6
  #define PTC7 ((struct _hc08_bits *)(&PTC))->bit7

VOLDATA UINT8 at 0x03 PTD;     /* Port D Data Register */
  #define PTD0 ((struct _hc08_bits *)(&PTD))->bit0
  #define PTD1 ((struct _hc08_bits *)(&PTD))->bit1
  #define PTD2 ((struct _hc08_bits *)(&PTD))->bit2
  #define PTD3 ((struct _hc08_bits *)(&PTD))->bit3
  #define PTD4 ((struct _hc08_bits *)(&PTD))->bit4
  #define PTD5 ((struct _hc08_bits *)(&PTD))->bit5
  #define PTD6 ((struct _hc08_bits *)(&PTD))->bit6
  #define PTD7 ((struct _hc08_bits *)(&PTD))->bit7

VOLDATA UINT8 at 0x04 DDRA;    /* Data Direction Register A */
  #define DDRA0 ((struct _hc08_bits *)(&DDRA))->bit0
  #define DDRA1 ((struct _hc08_bits *)(&DDRA))->bit1
  #define DDRA2 ((struct _hc08_bits *)(&DDRA))->bit2
  #define DDRA3 ((struct _hc08_bits *)(&DDRA))->bit3
  #define DDRA4 ((struct _hc08_bits *)(&DDRA))->bit4
  #define DDRA5 ((struct _hc08_bits *)(&DDRA))->bit5
  #define DDRA6 ((struct _hc08_bits *)(&DDRA))->bit6
  #define DDRA7 ((struct _hc08_bits *)(&DDRA))->bit7

VOLDATA UINT8 at 0x05 DDRB;    /* Data Direction Register B */
  #define DDRB0 ((struct _hc08_bits *)(&DDRB))->bit0
  #define DDRB1 ((struct _hc08_bits *)(&DDRB))->bit1
  #define DDRB2 ((struct _hc08_bits *)(&DDRB))->bit2
  #define DDRB3 ((struct _hc08_bits *)(&DDRB))->bit3
  #define DDRB4 ((struct _hc08_bits *)(&DDRB))->bit4
  #define DDRB5 ((struct _hc08_bits *)(&DDRB))->bit5
  #define DDRB6 ((struct _hc08_bits *)(&DDRB))->bit6
  #define DDRB7 ((struct _hc08_bits *)(&DDRB))->bit7

VOLDATA UINT8 at 0x06 DDRC;    /* Data Direction Register C */
  #define DDRC0 ((struct _hc08_bits *)(&DDRC))->bit0
  #define DDRC1 ((struct _hc08_bits *)(&DDRC))->bit1
  #define DDRC2 ((struct _hc08_bits *)(&DDRC))->bit2
  #define DDRC3 ((struct _hc08_bits *)(&DDRC))->bit3
  #define DDRC4 ((struct _hc08_bits *)(&DDRC))->bit4
  #define DDRC5 ((struct _hc08_bits *)(&DDRC))->bit5
  #define DDRC6 ((struct _hc08_bits *)(&DDRC))->bit6
  #define DDRC7 ((struct _hc08_bits *)(&DDRC))->bit7

VOLDATA UINT8 at 0x07 DDRD;    /* Data Direction Register D */
  #define DDRD0 ((struct _hc08_bits *)(&DDRD))->bit0
  #define DDRD1 ((struct _hc08_bits *)(&DDRD))->bit1
  #define DDRD2 ((struct _hc08_bits *)(&DDRD))->bit2
  #define DDRD3 ((struct _hc08_bits *)(&DDRD))->bit3
  #define DDRD4 ((struct _hc08_bits *)(&DDRD))->bit4
  #define DDRD5 ((struct _hc08_bits *)(&DDRD))->bit5
  #define DDRD6 ((struct _hc08_bits *)(&DDRD))->bit6
  #define DDRD7 ((struct _hc08_bits *)(&DDRD))->bit7

VOLDATA UINT8 at 0x08 PTE;     /* Port E Data Register */
  #define PTE0 ((struct _hc08_bits *)(&PTE))->bit0
  #define PTE1 ((struct _hc08_bits *)(&PTE))->bit1
  #define PTE2 ((struct _hc08_bits *)(&PTE))->bit2
  #define PTE3 ((struct _hc08_bits *)(&PTE))->bit3
  #define PTE4 ((struct _hc08_bits *)(&PTE))->bit4
  #define PTE5 ((struct _hc08_bits *)(&PTE))->bit5
  #define PTE6 ((struct _hc08_bits *)(&PTE))->bit6
  #define PTE7 ((struct _hc08_bits *)(&PTE))->bit7

VOLDATA UINT8 at 0x09 DDRE;    /* Data Direction Register E */
  #define DDRE0 ((struct _hc08_bits *)(&DDRE))->bit0
  #define DDRE1 ((struct _hc08_bits *)(&DDRE))->bit1
  #define DDRE2 ((struct _hc08_bits *)(&DDRE))->bit2
  #define DDRE3 ((struct _hc08_bits *)(&DDRE))->bit3
  #define DDRE4 ((struct _hc08_bits *)(&DDRE))->bit4
  #define DDRE5 ((struct _hc08_bits *)(&DDRE))->bit5
  #define DDRE6 ((struct _hc08_bits *)(&DDRE))->bit6
  #define DDRE7 ((struct _hc08_bits *)(&DDRE))->bit7

VOLDATA UINT8 at 0x0a TSC;     /* TIM Status and Control */
  #define PS0   ((struct _hc08_bits *)(&TSC))->bit0
  #define PS1   ((struct _hc08_bits *)(&TSC))->bit1
  #define PS2   ((struct _hc08_bits *)(&TSC))->bit2
  #define TRST  ((struct _hc08_bits *)(&TSC))->bit4
  #define TSTOP ((struct _hc08_bits *)(&TSC))->bit5
  #define TOIE  ((struct _hc08_bits *)(&TSC))->bit6
  #define TOF   ((struct _hc08_bits *)(&TSC))->bit7

VOLDATA UINT16 at 0x0c TCNT;   /* TIM Counter High & Low Registers */
VOLDATA UINT8 at 0x0c TCNTH;   /* TIM Counter Register High */
VOLDATA UINT8 at 0x0d TCNTL;   /* TIM Counter Register Low */

VOLDATA UINT16 at 0x0e TMOD;   /* TIM Counter Modulo High & Low Registers */
VOLDATA UINT8 at 0x0e TMODH;   /* TIM Counter Modulo Register High */
VOLDATA UINT8 at 0x0f TMODL;   /* TIM Counter Modulo Register Low */

VOLDATA UINT8 at 0x10 TSC0;    /* TIM Channel 0 Status and Control Register */
  #define CH0MAX ((struct _hc08_bits *)(&TSC0))->bit0
  #define TOV0   ((struct _hc08_bits *)(&TSC0))->bit1
  #define ELS0A  ((struct _hc08_bits *)(&TSC0))->bit2
  #define ELS0B  ((struct _hc08_bits *)(&TSC0))->bit3
  #define MS0A   ((struct _hc08_bits *)(&TSC0))->bit4
  #define MS0B   ((struct _hc08_bits *)(&TSC0))->bit5
  #define CH0IE  ((struct _hc08_bits *)(&TSC0))->bit6
  #define CH0F   ((struct _hc08_bits *)(&TSC0))->bit7

VOLDATA UINT16 at 0x11 TCH0;   /* TIM Channel 0 High & Low Registers */
VOLDATA UINT8 at 0x11 TCH0H;   /* TIM Channel 0 Register High */
VOLDATA UINT8 at 0x12 TCH0L;   /* TIM Channel 0 Register Low */

VOLDATA UINT8 at 0x13 TSC1;    /* TIM Channel 1 Status and Control Register */
  #define CH1MAX ((struct _hc08_bits *)(&TSC1))->bit0
  #define TOV1   ((struct _hc08_bits *)(&TSC1))->bit1
  #define ELS1A  ((struct _hc08_bits *)(&TSC1))->bit2
  #define ELS1B  ((struct _hc08_bits *)(&TSC1))->bit3
  #define MS1A   ((struct _hc08_bits *)(&TSC1))->bit4
  #define CH1IE  ((struct _hc08_bits *)(&TSC1))->bit6
  #define CH1F   ((struct _hc08_bits *)(&TSC1))->bit7

VOLDATA UINT16 at 0x14 TCH1;   /* TIM Channel 1 High & Low Registers */
VOLDATA UINT8 at 0x14 TCH1H;   /* TIM Channel 1 Register High */
VOLDATA UINT8 at 0x15 TCH1L;   /* TIM Channel 1 Register Low */

VOLDATA UINT8 at 0x16 KBSCR;   /* Keyboard Status and Control Register */
  #define MODEK  ((struct _hc08_bits *)(&KBSCR))->bit0
  #define IMASKK ((struct _hc08_bits *)(&KBSCR))->bit1
  #define ACKK   ((struct _hc08_bits *)(&KBSCR))->bit2
  #define KEYF   ((struct _hc08_bits *)(&KBSCR))->bit3

VOLDATA UINT8 at 0x17 KBIER;   /* Keyboard Interrupt Enable Register */
  #define KBIE0 ((struct _hc08_bits *)(&KBIER))->bit0
  #define KBIE1 ((struct _hc08_bits *)(&KBIER))->bit1
  #define KBIE2 ((struct _hc08_bits *)(&KBIER))->bit2
  #define KBIE3 ((struct _hc08_bits *)(&KBIER))->bit3
  #define KBIE4 ((struct _hc08_bits *)(&KBIER))->bit4
  #define KBIE5 ((struct _hc08_bits *)(&KBIER))->bit5
  #define KBIE6 ((struct _hc08_bits *)(&KBIER))->bit6
  #define KBIE7 ((struct _hc08_bits *)(&KBIER))->bit7

VOLDATA UINT8 at 0x18 UIR2;   /* USB Interrupt Register 2 */
  #define RXD0FR  ((struct _hc08_bits *)(&UIR2))->bit0
  #define TXD0FR  ((struct _hc08_bits *)(&UIR2))->bit1
  #define RESUMFR ((struct _hc08_bits *)(&UIR2))->bit2
  #define TXD1FR  ((struct _hc08_bits *)(&UIR2))->bit3
  #define RXD2FR  ((struct _hc08_bits *)(&UIR2))->bit4
  #define TXD2FR  ((struct _hc08_bits *)(&UIR2))->bit5
  #define RSTFR   ((struct _hc08_bits *)(&UIR2))->bit6
  #define EOPFR   ((struct _hc08_bits *)(&UIR2))->bit7

VOLDATA UINT8 at 0x19 UCR2;   /* USB Control Register 2 */
  #define TP2SIZ0 ((struct _hc08_bits *)(&UCR2))->bit0
  #define TP2SIZ1 ((struct _hc08_bits *)(&UCR2))->bit1
  #define TP2SIZ2 ((struct _hc08_bits *)(&UCR2))->bit2
  #define TP2SIZ3 ((struct _hc08_bits *)(&UCR2))->bit3
  #define RX2E    ((struct _hc08_bits *)(&UCR2))->bit4
  #define TX2E    ((struct _hc08_bits *)(&UCR2))->bit5
  #define STALL2  ((struct _hc08_bits *)(&UCR2))->bit6
  #define T2SEQ   ((struct _hc08_bits *)(&UCR2))->bit7

VOLDATA UINT8 at 0x1a UCR3;   /* USB Control Register 3 */
  #define ENABLE1 ((struct _hc08_bits *)(&UCR3))->bit0
  #define ENABLE2 ((struct _hc08_bits *)(&UCR3))->bit1
  #define PULLEN  ((struct _hc08_bits *)(&UCR3))->bit2
  #define ISTALL0 ((struct _hc08_bits *)(&UCR3))->bit4
  #define OSTALL0 ((struct _hc08_bits *)(&UCR3))->bit5
  #define TX1STR  ((struct _hc08_bits *)(&UCR3))->bit6
  #define TX1ST   ((struct _hc08_bits *)(&UCR3))->bit7

VOLDATA UINT8 at 0x1b UCR4;   /* USB Control Register 4 */
  #define FDM   ((struct _hc08_bits *)(&UCR4))->bit0
  #define FDP   ((struct _hc08_bits *)(&UCR4))->bit1
  #define FUSB0 ((struct _hc08_bits *)(&UCR4))->bit2

VOLDATA UINT8 at 0x1c IOCR;   /* IRQ Option Control Register */
  #define IRQPD  ((struct _hc08_bits *)(&IOCR))->bit0
  #define PTE4IE ((struct _hc08_bits *)(&IOCR))->bit1
  #define PTE4IF ((struct _hc08_bits *)(&IOCR))->bit2

VOLDATA UINT8 at 0x1d POCR;   /* Port Option Control Register */
 #define PAP     ((struct _hc08_bits *)(&POCR))->bit0
 #define PBP     ((struct _hc08_bits *)(&POCR))->bit1
 #define PCP     ((struct _hc08_bits *)(&POCR))->bit2
 #define PTE3P   ((struct _hc08_bits *)(&POCR))->bit3
 #define PTE4P   ((struct _hc08_bits *)(&POCR))->bit4
 #define PTDILDD ((struct _hc08_bits *)(&POCR))->bit5
 #define PTDLDD  ((struct _hc08_bits *)(&POCR))->bit6
 #define PTE20P  ((struct _hc08_bits *)(&POCR))->bit7

VOLDATA UINT8 at 0x1e ISCR;   /* IRQ Status and Control Register */
  #define MODE  ((struct _hc08_bits *)(&ISCR))->bit0
  #define IMASK ((struct _hc08_bits *)(&ISCR))->bit1
  #define ACK   ((struct _hc08_bits *)(&ISCR))->bit2
  #define IRQF  ((struct _hc08_bits *)(&ISCR))->bit3

VOLDATA UINT8 at 0x1f CONFIG; /* Configuration Register 1 */
/* CONFIG1 is one-time writeable, so can't use bitfields */

VOLDATA UINT8 at 0x20 UE0D0;  /* USB Endpoint 0 Data Register 0 */
VOLDATA UINT8 at 0x21 UE0D1;  /* USB Endpoint 0 Data Register 1 */
VOLDATA UINT8 at 0x22 UE0D2;  /* USB Endpoint 0 Data Register 2 */
VOLDATA UINT8 at 0x23 UE0D3;  /* USB Endpoint 0 Data Register 3 */
VOLDATA UINT8 at 0x24 UE0D4;  /* USB Endpoint 0 Data Register 4 */
VOLDATA UINT8 at 0x25 UE0D5;  /* USB Endpoint 0 Data Register 5 */
VOLDATA UINT8 at 0x26 UE0D6;  /* USB Endpoint 0 Data Register 6 */
VOLDATA UINT8 at 0x27 UE0D7;  /* USB Endpoint 0 Data Register 7 */

VOLDATA UINT8 at 0x28 UE1D0;  /* USB Endpoint 1 Data Register 0 */
VOLDATA UINT8 at 0x29 UE1D1;  /* USB Endpoint 1 Data Register 1 */
VOLDATA UINT8 at 0x2a UE1D2;  /* USB Endpoint 1 Data Register 2 */
VOLDATA UINT8 at 0x2b UE1D3;  /* USB Endpoint 1 Data Register 3 */
VOLDATA UINT8 at 0x2c UE1D4;  /* USB Endpoint 1 Data Register 4 */
VOLDATA UINT8 at 0x2d UE1D5;  /* USB Endpoint 1 Data Register 5 */
VOLDATA UINT8 at 0x2e UE1D6;  /* USB Endpoint 1 Data Register 6 */
VOLDATA UINT8 at 0x2f UE1D7;  /* USB Endpoint 1 Data Register 7 */

VOLDATA UINT8 at 0x30 UE2D0;  /* USB Endpoint 2 Data Register 0 */
VOLDATA UINT8 at 0x31 UE2D1;  /* USB Endpoint 2 Data Register 1 */
VOLDATA UINT8 at 0x32 UE2D2;  /* USB Endpoint 2 Data Register 2 */
VOLDATA UINT8 at 0x33 UE2D3;  /* USB Endpoint 2 Data Register 3 */
VOLDATA UINT8 at 0x34 UE2D4;  /* USB Endpoint 2 Data Register 4 */
VOLDATA UINT8 at 0x35 UE2D5;  /* USB Endpoint 2 Data Register 5 */
VOLDATA UINT8 at 0x36 UE2D6;  /* USB Endpoint 2 Data Register 6 */
VOLDATA UINT8 at 0x37 UE2D7;  /* USB Endpoint 2 Data Register 7 */

VOLDATA UINT8 at 0x38 UADDR;  /* USB Address Register */
 #define USBEN ((struct _hc08_bits *)(&UADDR))->bit7

VOLDATA UINT8 at 0x39 UIR0;   /* USB Interrupt Register 0 */
  #define RXD0IE  ((struct _hc08_bits *)(&UIR0))->bit0
  #define TXD0IE  ((struct _hc08_bits *)(&UIR0))->bit1
  #define TXD1IE  ((struct _hc08_bits *)(&UIR0))->bit3
  #define RXD2IE  ((struct _hc08_bits *)(&UIR0))->bit4
  #define TXD2IE  ((struct _hc08_bits *)(&UIR0))->bit5
  #define SUSPND  ((struct _hc08_bits *)(&UIR0))->bit6
  #define EOPIE   ((struct _hc08_bits *)(&UIR0))->bit7

VOLDATA UINT8 at 0x3a UIR1;   /* USB Interrupt Register 1 */
  #define RXD0F   ((struct _hc08_bits *)(&UIR1))->bit0
  #define TXD0F   ((struct _hc08_bits *)(&UIR1))->bit1
  #define RESUMF  ((struct _hc08_bits *)(&UIR1))->bit2
  #define TXD1F   ((struct _hc08_bits *)(&UIR1))->bit3
  #define RXD2F   ((struct _hc08_bits *)(&UIR1))->bit4
  #define TXD2F   ((struct _hc08_bits *)(&UIR1))->bit5
  #define RSTF    ((struct _hc08_bits *)(&UIR1))->bit6
  #define EOPF    ((struct _hc08_bits *)(&UIR1))->bit7

VOLDATA UINT8 at 0x3b UCR0;   /* USB Control Register 0 */
  #define TP0SIZ0 ((struct _hc08_bits *)(&UCR0))->bit0
  #define TP0SIZ1 ((struct _hc08_bits *)(&UCR0))->bit1
  #define TP0SIZ2 ((struct _hc08_bits *)(&UCR0))->bit2
  #define TP0SIZ3 ((struct _hc08_bits *)(&UCR0))->bit3
  #define RX0E    ((struct _hc08_bits *)(&UCR0))->bit4
  #define TX0E    ((struct _hc08_bits *)(&UCR0))->bit5
  #define T0SEQ   ((struct _hc08_bits *)(&UCR0))->bit7

VOLDATA UINT8 at 0x3c UCR1;   /* USB Control Register 1 */
  #define TP1SIZ0 ((struct _hc08_bits *)(&UCR1))->bit0
  #define TP1SIZ1 ((struct _hc08_bits *)(&UCR1))->bit1
  #define TP1SIZ2 ((struct _hc08_bits *)(&UCR1))->bit2
  #define TP1SIZ3 ((struct _hc08_bits *)(&UCR1))->bit3
  #define FRESUM  ((struct _hc08_bits *)(&UCR1))->bit4
  #define TX1E    ((struct _hc08_bits *)(&UCR1))->bit5
  #define STALL1  ((struct _hc08_bits *)(&UCR1))->bit6
  #define T1SEQ   ((struct _hc08_bits *)(&UCR1))->bit7

VOLDATA UINT8 at 0x3d USR0;   /* USB Status Register 0 */
  #define RP0SIZ0 ((struct _hc08_bits *)(&USR0))->bit0
  #define RP0SIZ1 ((struct _hc08_bits *)(&USR0))->bit1
  #define RP0SIZ2 ((struct _hc08_bits *)(&USR0))->bit2
  #define RP0SIZ3 ((struct _hc08_bits *)(&USR0))->bit3
  #define SETUP   ((struct _hc08_bits *)(&USR0))->bit6
  #define R0SEQ   ((struct _hc08_bits *)(&USR0))->bit7

VOLDATA UINT8 at 0x3e USR1;   /* USB Status Register 1 */
  #define RP2SIZ0 ((struct _hc08_bits *)(&USR1))->bit0
  #define RP2SIZ1 ((struct _hc08_bits *)(&USR1))->bit1
  #define RP2SIZ2 ((struct _hc08_bits *)(&USR1))->bit2
  #define RP2SIZ3 ((struct _hc08_bits *)(&USR1))->bit3
  #define TXSTL   ((struct _hc08_bits *)(&USR1))->bit4
  #define TXNAK   ((struct _hc08_bits *)(&USR1))->bit5
  #define TXACK   ((struct _hc08_bits *)(&USR1))->bit6
  #define R2SEQ   ((struct _hc08_bits *)(&USR1))->bit7

VOLXDATA UINT8 at 0xfe00 BSR;     /* Break Status Register */
  #define SBSW ((struct _hc08_bits *)(&BSR))->bit1

VOLXDATA UINT8 at 0xfe01 RSR;    /* Reset Status Register */
  #define LVI  ((struct _hc08_bits *)(&RSR))->bit1
  #define USB  ((struct _hc08_bits *)(&RSR))->bit2
  #define ILAD ((struct _hc08_bits *)(&RSR))->bit3
  #define ILOP ((struct _hc08_bits *)(&RSR))->bit4
  #define COP  ((struct _hc08_bits *)(&RSR))->bit5
  #define PIN  ((struct _hc08_bits *)(&RSR))->bit6
  #define POR  ((struct _hc08_bits *)(&RSR))->bit7

VOLXDATA UINT8 at 0xfe03 BFCR;    /* Break Flag Control Register */
  #define BFCE ((struct _hc08_bits *)(&BFCR))->bit7

VOLXDATA UINT8 at 0xfe04 INT1;    /* Interrupt Status Register 1 */
  #define IF1 ((struct _hc08_bits *)(&INT1))->bit2
  #define IF2 ((struct _hc08_bits *)(&INT1))->bit3
  #define IF3 ((struct _hc08_bits *)(&INT1))->bit4
  #define IF4 ((struct _hc08_bits *)(&INT1))->bit5
  #define IF5 ((struct _hc08_bits *)(&INT1))->bit6
  #define IF6 ((struct _hc08_bits *)(&INT1))->bit7

VOLXDATA UINT8 at 0xfe08 FLCR;    /* FLASH Control Register */
  #define PGM   ((struct _hc08_bits *)(&FLCR))->bit0
  #define ERASE ((struct _hc08_bits *)(&FLCR))->bit1
  #define MASS  ((struct _hc08_bits *)(&FLCR))->bit2
  #define HVEN  ((struct _hc08_bits *)(&FLCR))->bit3

VOLXDATA UINT8 at 0xfe09 FLBPR;    /* FLASH Block Protect Register */
  #define BPR0 ((struct _hc08_bits *)(&FLBPR))->bit0
  #define BPR1 ((struct _hc08_bits *)(&FLBPR))->bit1
  #define BPR2 ((struct _hc08_bits *)(&FLBPR))->bit2
  #define BPR3 ((struct _hc08_bits *)(&FLBPR))->bit3
  #define BPR4 ((struct _hc08_bits *)(&FLBPR))->bit4
  #define BPR5 ((struct _hc08_bits *)(&FLBPR))->bit5
  #define BPR6 ((struct _hc08_bits *)(&FLBPR))->bit6
  #define BPR7 ((struct _hc08_bits *)(&FLBPR))->bit7

VOLXDATA UINT16 at 0xfe0c BRK;    /* Break Address High & Low Registers */
VOLXDATA UINT8 at 0xfe0c BRKH;    /* Break Address High Register */
VOLXDATA UINT8 at 0xfe0d BRKL;    /* Break Address Low Register */

VOLXDATA UINT8 at 0xfe0e BRKSCR;  /* Break Status and Control Register */
  #define BRKA ((struct _hc08_bits *)(&BRKSCR))->bit6
  #define BRKE ((struct _hc08_bits *)(&BRKSCR))->bit7

VOLXDATA UINT8 at 0xffff COPCTL;  /* COP Control Register */

#endif

