
#if _HTC_VER_MAJOR_ >= 9
 #ifndef _HTC_H_
  #warning Device header file included directly. Use #include <htc.h> instead.
 #endif
#elif !defined(_PIC18_H)
 #warning Device header file included directly. Use #include <pic18.h> instead.
#endif

 /* header file for the MICROCHIP PIC18 microcontrollers
  * PIC18F6621
  * PIC18F6525
  * PIC18F8621
  * PIC18F8525
 */

#ifndef	__PIC18F6X2X_H

#define	__PIC18F6X2X_H

#if defined(_18F6621) || defined(_18F6525)
#define _18F6X2X
#endif

#if defined(_18F6525) || defined(_18F8525)
#define _18FX525
#endif

extern volatile near unsigned char	TOSU		@ 0xFFF;
extern volatile near unsigned char	TOSH		@ 0xFFE;
extern volatile near unsigned char	TOSL		@ 0xFFD;
extern volatile near unsigned char	STKPTR		@ 0xFFC;
extern volatile near unsigned char	PCLATU		@ 0xFFB;
extern volatile near unsigned char	PCLATH		@ 0xFFA;
extern volatile near unsigned char	PCL		@ 0xFF9;
extern volatile far  unsigned char *	TBLPTR		@ 0xFF6;
extern volatile near unsigned char	TBLPTRU		@ 0xFF8;
extern volatile near unsigned char	TBLPTRH		@ 0xFF7;
extern volatile near unsigned char	TBLPTRL		@ 0xFF6;
extern volatile near unsigned char	TABLAT		@ 0xFF5;
extern volatile near unsigned char	PRODH		@ 0xFF4;
extern volatile near unsigned char	PRODL		@ 0xFF3;
extern volatile near unsigned char	INTCON		@ 0xFF2;
extern          near unsigned char	INTCON2		@ 0xFF1;
extern volatile near unsigned char	INTCON3		@ 0xFF0;
extern volatile near unsigned char	INDF0		@ 0xFEF;
extern volatile near unsigned char	POSTINC0	@ 0xFEE;
extern volatile near unsigned char	POSTDEC0	@ 0xFED;
extern volatile near unsigned char	PREINC0		@ 0xFEC;
extern volatile near unsigned char	PLUSW0		@ 0xFEB;
extern volatile near unsigned char	FSR0H		@ 0xFEA;
extern volatile near unsigned char	FSR0L		@ 0xFE9;
extern volatile near unsigned char	WREG		@ 0xFE8;
extern volatile near unsigned char	INDF1		@ 0xFE7;
extern volatile near unsigned char	POSTINC1	@ 0xFE6;
extern volatile near unsigned char	POSTDEC1	@ 0xFE5;
extern volatile near unsigned char	PREINC1		@ 0xFE4;
extern volatile near unsigned char	PLUSW1		@ 0xFE3;
extern volatile near unsigned char	FSR1H		@ 0xFE2;
extern volatile near unsigned char	FSR1L		@ 0xFE1;
extern          near unsigned char	BSR		@ 0xFE0;
extern volatile near unsigned char	INDF2		@ 0xFDF;
extern volatile near unsigned char	POSTINC2	@ 0xFDE;
extern volatile near unsigned char	POSTDEC2	@ 0xFDD;
extern volatile near unsigned char	PREINC2		@ 0xFDC;
extern volatile near unsigned char	PLUSW2		@ 0xFDB;
extern volatile near unsigned char	FSR2H		@ 0xFDA;
extern volatile near unsigned char	FSR2L		@ 0xFD9;
extern volatile near unsigned char	STATUS		@ 0xFD8;
extern volatile near unsigned char	TMR0H		@ 0xFD7;
extern volatile near unsigned char	TMR0L		@ 0xFD6;
// 16-Bit definition
extern volatile near unsigned int	TMR0		@ 0xFD6;
extern          near unsigned char	T0CON		@ 0xFD5;
extern volatile near unsigned char	OSCCON		@ 0xFD3;
extern volatile near unsigned char	LVDCON		@ 0xFD2;
extern volatile near unsigned char	WDTCON		@ 0xFD1;
extern volatile near unsigned char	RCON		@ 0xFD0;
extern volatile near unsigned char	TMR1H		@ 0xFCF;
extern volatile near unsigned char	TMR1L		@ 0xFCE;
// 16-Bit definition
extern volatile near unsigned int	TMR1		@ 0xFCE;
extern          near unsigned char	T1CON		@ 0xFCD;
extern volatile near unsigned char	TMR2		@ 0xFCC;
extern          near unsigned char	PR2		@ 0xFCB;
extern          near unsigned char	T2CON		@ 0xFCA;
extern volatile near unsigned char	SSPBUF		@ 0xFC9;
extern          near unsigned char	SSPADD		@ 0xFC8;
extern volatile near unsigned char	SSPSTAT		@ 0xFC7;
extern volatile near unsigned char	SSPCON1		@ 0xFC6;
extern volatile near unsigned char	SSPCON2		@ 0xFC5;
extern volatile near unsigned char	ADRESH		@ 0xFC4;
extern volatile near unsigned char	ADRESL		@ 0xFC3;
// 16-Bit definition
extern volatile near unsigned int	ADRES		@ 0xFC3;
extern volatile near unsigned char	ADCON0		@ 0xFC2;
extern          near unsigned char	ADCON1		@ 0xFC1;
extern          near unsigned char	ADCON2		@ 0xFC0;
extern volatile near unsigned char	CCPR1H		@ 0xFBF;
extern volatile near unsigned char	CCPR1L		@ 0xFBE;
// 16-Bit definition
extern volatile near unsigned int	CCPR1		@ 0xFBE;
extern volatile near unsigned char	CCP1CON		@ 0xFBD;
extern volatile near unsigned char	CCPR2H		@ 0xFBC;
extern volatile near unsigned char	CCPR2L		@ 0xFBB;
// 16-Bit definition
extern volatile near unsigned int	CCPR2		@ 0xFBB;
extern volatile near unsigned char	CCP2CON		@ 0xFBA;
extern volatile near unsigned char	CCPR3H		@ 0xFB9;
extern volatile near unsigned char	CCPR3L		@ 0xFB8;
// 16-Bit definition
extern volatile near unsigned int	CCPR3		@ 0xFB8;
extern volatile near unsigned char	CCP3CON		@ 0xFB7;
extern volatile near unsigned char	ECCP1AS		@ 0xFB6;
extern volatile near unsigned char	CVRCON		@ 0xFB5;
extern volatile near unsigned char	CMCON		@ 0xFB4;
extern volatile near unsigned char	TMR3H		@ 0xFB3;
extern volatile near unsigned char	TMR3L		@ 0xFB2;
// 16-Bit definition
extern volatile near unsigned int	TMR3		@ 0xFB2;
extern          near unsigned char	T3CON		@ 0xFB1;
extern volatile near unsigned char	PSPCON		@ 0xFB0;
extern 		near unsigned char	SPBRG1		@ 0xFAF;
extern volatile near unsigned char	RCREG1		@ 0xFAE;
extern volatile near unsigned char	TXREG1		@ 0xFAD;
extern volatile near unsigned char	TXSTA1		@ 0xFAC;
extern volatile near unsigned char	RCSTA1		@ 0xFAB;
// alternate definitions for compatability with mono USART devices
extern          near unsigned char	SPBRG		@ 0xFAF;
extern volatile near unsigned char	RCREG		@ 0xFAE;
extern volatile near unsigned char	TXREG		@ 0xFAD;
extern volatile near unsigned char	TXSTA		@ 0xFAC;
extern volatile near unsigned char	RCSTA		@ 0xFAB;
extern          near unsigned char	EEADRH		@ 0xFAA;
extern          near unsigned char	EEADR		@ 0xFA9;
extern volatile near unsigned char	EEDATA		@ 0xFA8;
extern volatile near unsigned char	EECON2		@ 0xFA7;
extern volatile near unsigned char	EECON1		@ 0xFA6;
extern          near unsigned char	IPR3		@ 0xFA5;
extern volatile near unsigned char	PIR3		@ 0xFA4;
extern          near unsigned char	PIE3		@ 0xFA3;
extern          near unsigned char	IPR2		@ 0xFA2;
extern volatile near unsigned char	PIR2		@ 0xFA1;
extern          near unsigned char	PIE2		@ 0xFA0;
extern          near unsigned char	IPR1		@ 0xF9F;
extern volatile near unsigned char	PIR1		@ 0xF9E;
extern          near unsigned char	PIE1		@ 0xF9D;
#ifndef _18F6X2X
extern          near unsigned char	MEMCON		@ 0xF9C;
extern volatile near unsigned char	TRISJ		@ 0xF9A;
extern volatile near unsigned char	TRISH		@ 0xF99;
#endif
extern volatile near unsigned char	TRISG		@ 0xF98;
extern volatile near unsigned char	TRISF		@ 0xF97;
extern volatile near unsigned char	TRISE		@ 0xF96;
extern volatile near unsigned char	TRISD		@ 0xF95;
extern volatile near unsigned char	TRISC		@ 0xF94;
extern volatile near unsigned char	TRISB		@ 0xF93;
extern volatile near unsigned char	TRISA		@ 0xF92;
#ifndef _18F6X2X
extern volatile near unsigned char	LATJ		@ 0xF91;
extern volatile near unsigned char	LATH		@ 0xF90;
#endif
extern volatile near unsigned char	LATG		@ 0xF8F;
extern volatile near unsigned char	LATF		@ 0xF8E;
extern volatile near unsigned char	LATE		@ 0xF8D;
extern volatile near unsigned char	LATD		@ 0xF8C;
extern volatile near unsigned char	LATC		@ 0xF8B;
extern volatile near unsigned char	LATB		@ 0xF8A;
extern volatile near unsigned char	LATA		@ 0xF89;
#ifndef _18F6X2X
extern volatile near unsigned char	PORTJ		@ 0xF88;
extern volatile near unsigned char	PORTH		@ 0xF87;
#endif
extern volatile near unsigned char	PORTG		@ 0xF86;
extern volatile near unsigned char	PORTF		@ 0xF85;
extern volatile near unsigned char	PORTE		@ 0xF84;
extern volatile near unsigned char	PORTD		@ 0xF83;
extern volatile near unsigned char	PORTC		@ 0xF82;
extern volatile near unsigned char	PORTB		@ 0xF81;
extern volatile near unsigned char	PORTA		@ 0xF80;
extern          near unsigned char	SPBRGH		@ 0xF7F;
extern          near unsigned char	SPBRGH1		@ 0xF7F; // Alternate def for compatibility
extern volatile near unsigned char	BAUDCON		@ 0xF7E;
extern          near unsigned char	SPBRGH2		@ 0xF7D;
extern volatile near unsigned char	BAUDCON2	@ 0xF7C;
extern          near unsigned char	ECCP1DEL	@ 0xF79;
extern volatile near unsigned char	TMR4		@ 0xF78;
extern          near unsigned char	PR4		@ 0xF77;
extern          near unsigned char	T4CON		@ 0xF76;
extern volatile near unsigned char	CCPR4H		@ 0xF75;
extern volatile near unsigned char	CCPR4L		@ 0xF74;
// 16-Bit definition
extern volatile near unsigned int	CCPR4		@ 0xF74;
extern volatile near unsigned char	CCP4CON		@ 0xF73;
extern volatile near unsigned char	CCPR5H		@ 0xF72;
extern volatile near unsigned char	CCPR5L		@ 0xF71;
// 16-Bit definition
extern volatile near unsigned int	CCPR5		@ 0xF71;
extern volatile near unsigned char	CCP5CON		@ 0xF70;
extern          near unsigned char	SPBRG2		@ 0xF6F;
extern volatile near unsigned char	RCREG2		@ 0xF6E;
extern volatile near unsigned char	TXREG2		@ 0xF6D;
extern volatile near unsigned char	TXSTA2		@ 0xF6C;
extern volatile near unsigned char	RCSTA2		@ 0xF6B;
extern volatile near unsigned char	ECCP3AS		@ 0xF6A;
extern          near unsigned char	ECCP3DEL	@ 0xF69;
extern volatile near unsigned char	ECCP2AS		@ 0xF68;
extern          near unsigned char	ECCP2DEL	@ 0xF67;


/* Definitions for STKPTR register */
extern volatile near bit	STKUNF		@ ((unsigned)&STKPTR*8)+6;
extern volatile near bit	STKFUL		@ ((unsigned)&STKPTR*8)+7;

/* Definitions for INTCON register */
extern volatile near bit	RBIF		@ ((unsigned)&INTCON*8)+0;
extern volatile near bit	INT0IF		@ ((unsigned)&INTCON*8)+1;
extern volatile near bit	TMR0IF		@ ((unsigned)&INTCON*8)+2;
extern          near bit	RBIE		@ ((unsigned)&INTCON*8)+3;
extern          near bit	INT0IE		@ ((unsigned)&INTCON*8)+4;
extern          near bit	TMR0IE		@ ((unsigned)&INTCON*8)+5;
extern          near bit	PEIE		@ ((unsigned)&INTCON*8)+6;
extern          near bit	GIE		@ ((unsigned)&INTCON*8)+7;
/* Alternate definitions for INTCON register */
extern          near bit	GIEL		@ ((unsigned)&INTCON*8)+6;
extern          near bit	GIEH		@ ((unsigned)&INTCON*8)+7;

/* Definitions for INTCON2 register */
extern          near bit	RBIP		@ ((unsigned)&INTCON2*8)+0;
extern          near bit	INT3IP		@ ((unsigned)&INTCON2*8)+1;
extern          near bit	TMR0IP		@ ((unsigned)&INTCON2*8)+2;
extern          near bit	INTEDG3		@ ((unsigned)&INTCON2*8)+3;
extern          near bit	INTEDG2		@ ((unsigned)&INTCON2*8)+4;
extern          near bit	INTEDG1		@ ((unsigned)&INTCON2*8)+5;
extern          near bit	INTEDG0		@ ((unsigned)&INTCON2*8)+6;
extern          near bit	RBPU		@ ((unsigned)&INTCON2*8)+7;

/* Definitions for INTCON3 register */
extern volatile near bit	INT1IF		@ ((unsigned)&INTCON3*8)+0;
extern volatile near bit	INT2IF		@ ((unsigned)&INTCON3*8)+1;
extern volatile near bit	INT3IF		@ ((unsigned)&INTCON3*8)+2;
extern          near bit	INT1IE		@ ((unsigned)&INTCON3*8)+3;
extern          near bit	INT2IE		@ ((unsigned)&INTCON3*8)+4;
extern          near bit	INT3IE		@ ((unsigned)&INTCON3*8)+5;
extern          near bit	INT1IP		@ ((unsigned)&INTCON3*8)+6;
extern          near bit	INT2IP		@ ((unsigned)&INTCON3*8)+7;

/* Definitions for STATUS register */
extern volatile near bit	CARRY		@ ((unsigned)&STATUS*8)+0;
extern volatile near bit	DC		@ ((unsigned)&STATUS*8)+1;
extern volatile near bit	ZERO		@ ((unsigned)&STATUS*8)+2;
extern volatile near bit	OV		@ ((unsigned)&STATUS*8)+3;
extern volatile near bit	NEGATIVE	@ ((unsigned)&STATUS*8)+4;

/* Definitions for T0CON register */
extern          near bit	T0PS0		@ ((unsigned)&T0CON*8)+0;
extern          near bit	T0PS1		@ ((unsigned)&T0CON*8)+1;
extern          near bit	T0PS2		@ ((unsigned)&T0CON*8)+2;
extern          near bit	PSA		@ ((unsigned)&T0CON*8)+3;
extern          near bit	T0SE		@ ((unsigned)&T0CON*8)+4;
extern          near bit	T0CS		@ ((unsigned)&T0CON*8)+5;
extern          near bit	T08BIT		@ ((unsigned)&T0CON*8)+6;
extern          near bit	TMR0ON		@ ((unsigned)&T0CON*8)+7;

/* Definitions for OSCCON register */
extern          near bit	SCS		@ ((unsigned)&OSCCON*8)+0;

/* Definitions for LVDCON register */
extern          near bit	LVDL0		@ ((unsigned)&LVDCON*8)+0;
extern          near bit	LVDL1		@ ((unsigned)&LVDCON*8)+1;
extern          near bit	LVDL2		@ ((unsigned)&LVDCON*8)+2;
extern          near bit	LVDL3		@ ((unsigned)&LVDCON*8)+3;
extern          near bit	LVDEN		@ ((unsigned)&LVDCON*8)+4;
extern volatile near bit	IRVST		@ ((unsigned)&LVDCON*8)+5;

/* Definitions for WDTCON register */
extern          near bit	SWDTE		@ ((unsigned)&WDTCON*8)+0;

/* Definitions for RCON register */
extern volatile near bit	BOR		@ ((unsigned)&RCON*8)+0;
extern volatile near bit	POR		@ ((unsigned)&RCON*8)+1;
extern volatile near bit	PD		@ ((unsigned)&RCON*8)+2;
extern volatile near bit	TO		@ ((unsigned)&RCON*8)+3;
extern volatile near bit	RI		@ ((unsigned)&RCON*8)+4;
extern          near bit	IPEN		@ ((unsigned)&RCON*8)+7;

/* Definitions for T1CON register */
extern          near bit	TMR1ON		@ ((unsigned)&T1CON*8)+0;
extern          near bit	TMR1CS		@ ((unsigned)&T1CON*8)+1;
extern          near bit	T1SYNC		@ ((unsigned)&T1CON*8)+2;
extern          near bit	T1OSCEN		@ ((unsigned)&T1CON*8)+3;
extern          near bit	T1CKPS0		@ ((unsigned)&T1CON*8)+4;
extern          near bit	T1CKPS1		@ ((unsigned)&T1CON*8)+5;
extern          near bit	T1RD16		@ ((unsigned)&T1CON*8)+7;

/* Definitions for T2CON register */
extern          near bit	T2CKPS0		@ ((unsigned)&T2CON*8)+0;
extern          near bit	T2CKPS1		@ ((unsigned)&T2CON*8)+1;
extern          near bit	TMR2ON		@ ((unsigned)&T2CON*8)+2;
extern          near bit	T2OUTPS0	@ ((unsigned)&T2CON*8)+3;
extern          near bit	T2OUTPS1	@ ((unsigned)&T2CON*8)+4;
extern          near bit	T2OUTPS2	@ ((unsigned)&T2CON*8)+5;
extern          near bit	T2OUTPS3	@ ((unsigned)&T2CON*8)+6;

/* Definitions for SSPSTAT register */
extern volatile near bit	BF		@ ((unsigned)&SSPSTAT*8)+0;
extern volatile near bit	UA		@ ((unsigned)&SSPSTAT*8)+1;
extern volatile near bit	RW		@ ((unsigned)&SSPSTAT*8)+2;
extern volatile near bit	START		@ ((unsigned)&SSPSTAT*8)+3;
extern volatile near bit	STOP		@ ((unsigned)&SSPSTAT*8)+4;
extern volatile near bit	DA		@ ((unsigned)&SSPSTAT*8)+5;
extern          near bit	CKE		@ ((unsigned)&SSPSTAT*8)+6;
extern          near bit	SMP		@ ((unsigned)&SSPSTAT*8)+7;

/* Definitions for SSPCON1 register */
extern          near bit	SSPM0		@ ((unsigned)&SSPCON1*8)+0;
extern          near bit	SSPM1		@ ((unsigned)&SSPCON1*8)+1;
extern          near bit	SSPM2		@ ((unsigned)&SSPCON1*8)+2;
extern          near bit	SSPM3		@ ((unsigned)&SSPCON1*8)+3;
extern volatile near bit	CKP		@ ((unsigned)&SSPCON1*8)+4;
extern          near bit	SSPEN		@ ((unsigned)&SSPCON1*8)+5;
extern volatile near bit	SSPOV		@ ((unsigned)&SSPCON1*8)+6;
extern volatile near bit	WCOL		@ ((unsigned)&SSPCON1*8)+7;

/* Definitions for SSPCON2 register */
extern          near bit	SEN		@ ((unsigned)&SSPCON2*8)+0;
extern volatile near bit	RSEN		@ ((unsigned)&SSPCON2*8)+1;
extern volatile near bit	PEN		@ ((unsigned)&SSPCON2*8)+2;
extern volatile near bit	RCEN		@ ((unsigned)&SSPCON2*8)+3;
extern volatile near bit	ACKEN		@ ((unsigned)&SSPCON2*8)+4;
extern volatile near bit	ACKDT		@ ((unsigned)&SSPCON2*8)+5;
extern volatile near bit	ACKSTAT		@ ((unsigned)&SSPCON2*8)+6;
extern          near bit	GCEN		@ ((unsigned)&SSPCON2*8)+7;

/* Definitions for ADCON0 register */
extern          near bit	ADON		@ ((unsigned)&ADCON0*8)+0;
extern volatile near bit	GODONE		@ ((unsigned)&ADCON0*8)+1;
extern          near bit	CHS0		@ ((unsigned)&ADCON0*8)+2;
extern          near bit	CHS1		@ ((unsigned)&ADCON0*8)+3;
extern          near bit	CHS2		@ ((unsigned)&ADCON0*8)+4;
extern          near bit	CHS3		@ ((unsigned)&ADCON0*8)+5;

/* Definitions for ADCON1 register */
extern          near bit	PCFG0		@ ((unsigned)&ADCON1*8)+0;
extern          near bit	PCFG1		@ ((unsigned)&ADCON1*8)+1;
extern          near bit	PCFG2		@ ((unsigned)&ADCON1*8)+2;
extern          near bit	PCFG3		@ ((unsigned)&ADCON1*8)+3;
extern          near bit	VCFG0		@ ((unsigned)&ADCON1*8)+4;
extern          near bit	VCFG1		@ ((unsigned)&ADCON1*8)+5;

/* Definitions for ADCON2 register */
extern          near bit	ADCS0		@ ((unsigned)&ADCON2*8)+0;
extern          near bit	ADCS1		@ ((unsigned)&ADCON2*8)+1;
extern          near bit	ADCS2		@ ((unsigned)&ADCON2*8)+2;
extern          near bit	ACQT0		@ ((unsigned)&ADCON2*8)+3;
extern          near bit	ACQT1		@ ((unsigned)&ADCON2*8)+4;
extern          near bit	ACQT2		@ ((unsigned)&ADCON2*8)+5;
extern          near bit	ADFM		@ ((unsigned)&ADCON2*8)+7;

/* Definitions for CCP1CON register */
extern          near bit	CCP1M0		@ ((unsigned)&CCP1CON*8)+0;
extern          near bit	CCP1M1		@ ((unsigned)&CCP1CON*8)+1;
extern          near bit	CCP1M2		@ ((unsigned)&CCP1CON*8)+2;
extern          near bit	CCP1M3		@ ((unsigned)&CCP1CON*8)+3;
extern          near bit	DC1B0		@ ((unsigned)&CCP1CON*8)+4;
extern          near bit	DC1B1		@ ((unsigned)&CCP1CON*8)+5;
extern          near bit	P1M0		@ ((unsigned)&CCP1CON*8)+6;
extern          near bit	P1M1		@ ((unsigned)&CCP1CON*8)+7;

/* Definitions for CCP2CON register */
extern          near bit	CCP2M0		@ ((unsigned)&CCP2CON*8)+0;
extern          near bit	CCP2M1		@ ((unsigned)&CCP2CON*8)+1;
extern          near bit	CCP2M2		@ ((unsigned)&CCP2CON*8)+2;
extern          near bit	CCP2M3		@ ((unsigned)&CCP2CON*8)+3;
extern          near bit	DC2B0		@ ((unsigned)&CCP2CON*8)+4;
extern          near bit	DC2B1		@ ((unsigned)&CCP2CON*8)+5;
extern          near bit	P2M0		@ ((unsigned)&CCP2CON*8)+6;
extern          near bit	P2M1		@ ((unsigned)&CCP2CON*8)+7;

/* Definitions for CCP3CON register */
extern          near bit	CCP3M0		@ ((unsigned)&CCP3CON*8)+0;
extern          near bit	CCP3M1		@ ((unsigned)&CCP3CON*8)+1;
extern          near bit	CCP3M2		@ ((unsigned)&CCP3CON*8)+2;
extern          near bit	CCP3M3		@ ((unsigned)&CCP3CON*8)+3;
extern volatile near bit	CCP3Y		@ ((unsigned)&CCP3CON*8)+4;
extern volatile near bit	CCP3X		@ ((unsigned)&CCP3CON*8)+5;
extern          near bit	P3M0		@ ((unsigned)&CCP3CON*8)+6;
extern          near bit	P3M1		@ ((unsigned)&CCP3CON*8)+7;

/* Alternate definitions for CCP3CON register for compatibilty*/
extern          near bit	DC3B0		@ ((unsigned)&CCP3CON*8)+4;
extern          near bit	DC3B1		@ ((unsigned)&CCP3CON*8)+5;

/* Definitions for ECCP1AS register */
extern          near bit	PSS1BD0		@ ((unsigned)&ECCP1AS*8)+0;
extern          near bit	PSS1BD1		@ ((unsigned)&ECCP1AS*8)+1;
extern          near bit	PSS1AC0		@ ((unsigned)&ECCP1AS*8)+2;
extern          near bit	PSS1AC1		@ ((unsigned)&ECCP1AS*8)+3;
extern          near bit	ECCP1AS0	@ ((unsigned)&ECCP1AS*8)+4;
extern          near bit	ECCP1AS1	@ ((unsigned)&ECCP1AS*8)+5;
extern          near bit	ECCP1AS2	@ ((unsigned)&ECCP1AS*8)+6;
extern volatile near bit	ECCP1ASE	@ ((unsigned)&ECCP1AS*8)+7;

/* Definitions for CVRCON register */
extern          near bit	CVR0		@ ((unsigned)&CVRCON*8)+0;
extern          near bit	CVR1		@ ((unsigned)&CVRCON*8)+1;
extern          near bit	CVR2		@ ((unsigned)&CVRCON*8)+2;
extern          near bit	CVR3		@ ((unsigned)&CVRCON*8)+3;
extern          near bit	CVRSS		@ ((unsigned)&CVRCON*8)+4;
extern          near bit	CVRR		@ ((unsigned)&CVRCON*8)+5;
extern          near bit	CVROE		@ ((unsigned)&CVRCON*8)+6;
extern          near bit	CVREN		@ ((unsigned)&CVRCON*8)+7;

/* Definitions for CMCON register */
extern          near bit	CM0		@ ((unsigned)&CMCON*8)+0;
extern          near bit	CM1		@ ((unsigned)&CMCON*8)+1;
extern          near bit	CM2		@ ((unsigned)&CMCON*8)+2;
extern          near bit	CIS		@ ((unsigned)&CMCON*8)+3;
extern          near bit	C1INV		@ ((unsigned)&CMCON*8)+4;
extern          near bit	C2INV		@ ((unsigned)&CMCON*8)+5;
extern volatile near bit	C1OUT		@ ((unsigned)&CMCON*8)+6;
extern volatile near bit	C2OUT		@ ((unsigned)&CMCON*8)+7;

/* Definitions for T3CON register */
extern          near bit	TMR3ON		@ ((unsigned)&T3CON*8)+0;
extern          near bit	TMR3CS		@ ((unsigned)&T3CON*8)+1;
extern          near bit	T3SYNC		@ ((unsigned)&T3CON*8)+2;
extern          near bit	T3CCP1		@ ((unsigned)&T3CON*8)+3;
extern          near bit	T3CKPS0		@ ((unsigned)&T3CON*8)+4;
extern          near bit	T3CKPS1		@ ((unsigned)&T3CON*8)+5;
extern          near bit	T3CCP2		@ ((unsigned)&T3CON*8)+6;
extern          near bit	T3RD16		@ ((unsigned)&T3CON*8)+7;

/* Definitions for PSPCON register */
extern          near bit	PSPMODE		@ ((unsigned)&PSPCON*8)+4;
extern volatile near bit	IBOV		@ ((unsigned)&PSPCON*8)+5;
extern volatile near bit	OBF		@ ((unsigned)&PSPCON*8)+6;
extern volatile near bit	IBF		@ ((unsigned)&PSPCON*8)+7;

/* Definitions for TXSTA register */
extern volatile	near bit	TX9D1		@ ((unsigned)&TXSTA1*8)+0;	// 9th Bit of TX data
extern volatile	near bit	TRMT1		@ ((unsigned)&TXSTA1*8)+1;	// TX shift reg. status bit
extern 	near bit	BRGH1		@ ((unsigned)&TXSTA1*8)+2;	// high baud rate select
extern 	near bit	SENDB1		@ ((unsigned)&TXSTA1*8)+3;	// 
extern 	near bit	SYNC1		@ ((unsigned)&TXSTA1*8)+4;	// USART mode select
extern 	near bit	TXEN1		@ ((unsigned)&TXSTA1*8)+5;	// transmit enable bit
extern 	near bit	TX91		@ ((unsigned)&TXSTA1*8)+6;	// 8/9-bit TX data select
extern 	near bit	CSRC1		@ ((unsigned)&TXSTA1*8)+7;	// CLK source select
// Alternate definitions for compatibility with mono USART devices
extern volatile near bit	TX9D		@ ((unsigned)&TXSTA*8)+0;
extern volatile near bit	TRMT		@ ((unsigned)&TXSTA*8)+1;
extern          near bit	BRGH		@ ((unsigned)&TXSTA*8)+2;
extern 		near bit	SENDB		@ ((unsigned)&TXSTA*8)+3;
extern          near bit	SYNC		@ ((unsigned)&TXSTA*8)+4;
extern          near bit	TXEN		@ ((unsigned)&TXSTA*8)+5;
extern          near bit	TX9		@ ((unsigned)&TXSTA*8)+6;
extern          near bit	CSRC		@ ((unsigned)&TXSTA*8)+7;

/* Definitions for RCSTA register */
extern volatile	near bit	RX9D1		@ ((unsigned)&RCSTA1*8)+0;	// 9th Bit of RX data
extern volatile	near bit	OERR1		@ ((unsigned)&RCSTA1*8)+1;	// overrun error
extern volatile	near bit	FERR1		@ ((unsigned)&RCSTA1*8)+2;	// framing error
extern 	near bit	ADDEN1		@ ((unsigned)&RCSTA1*8)+3;	// address detect enable
extern 	near bit	CREN1		@ ((unsigned)&RCSTA1*8)+4;	// continuous recieve enable
extern 	near bit	SREN1		@ ((unsigned)&RCSTA1*8)+5;	// single recieve enable
extern 	near bit	RX91		@ ((unsigned)&RCSTA1*8)+6;	// 8/9-bit data reception
extern 	near bit	SPEN1		@ ((unsigned)&RCSTA1*8)+7;	// serial port enable
// Alternate definitions for compatibility with mono USART devices
extern volatile near bit	RX9D		@ ((unsigned)&RCSTA*8)+0;
extern volatile near bit	OERR		@ ((unsigned)&RCSTA*8)+1;
extern volatile near bit	FERR		@ ((unsigned)&RCSTA*8)+2;
extern          near bit	ADDEN		@ ((unsigned)&RCSTA*8)+3;
extern          near bit	CREN		@ ((unsigned)&RCSTA*8)+4;
extern          near bit	SREN		@ ((unsigned)&RCSTA*8)+5;
extern          near bit	RX9		@ ((unsigned)&RCSTA*8)+6;
extern          near bit	SPEN		@ ((unsigned)&RCSTA*8)+7;

/* Definitions for EECON1 register */
extern volatile near bit	RD		@ ((unsigned)&EECON1*8)+0;
extern volatile near bit	WR		@ ((unsigned)&EECON1*8)+1;
extern          near bit	WREN		@ ((unsigned)&EECON1*8)+2;
extern volatile near bit	WRERR		@ ((unsigned)&EECON1*8)+3;
extern volatile near bit	FREE		@ ((unsigned)&EECON1*8)+4;
extern          near bit	CFGS		@ ((unsigned)&EECON1*8)+6;
extern          near bit	EEPGD		@ ((unsigned)&EECON1*8)+7;

/* Definitions for IPR3 register */
extern          near bit	CCP3IP		@ ((unsigned)&IPR3*8)+0;
extern          near bit	CCP4IP		@ ((unsigned)&IPR3*8)+1;
extern          near bit	CCP5IP		@ ((unsigned)&IPR3*8)+2;
extern          near bit	TMR4IP		@ ((unsigned)&IPR3*8)+3;
extern          near bit	TX2IP		@ ((unsigned)&IPR3*8)+4;
extern          near bit	RC2IP		@ ((unsigned)&IPR3*8)+5;

/* Definitions for PIR3 register */
extern volatile near bit	CCP3IF		@ ((unsigned)&PIR3*8)+0;
extern volatile near bit	CCP4IF		@ ((unsigned)&PIR3*8)+1;
extern volatile near bit	CCP5IF		@ ((unsigned)&PIR3*8)+2;
extern volatile near bit	TMR4IF		@ ((unsigned)&PIR3*8)+3;
extern volatile near bit	TX2IF		@ ((unsigned)&PIR3*8)+4;
extern volatile near bit	RC2IF		@ ((unsigned)&PIR3*8)+5;

/* Definitions for PIE3 register */
extern          near bit	CCP3IE		@ ((unsigned)&PIE3*8)+0;
extern          near bit	CCP4IE		@ ((unsigned)&PIE3*8)+1;
extern          near bit	CCP5IE		@ ((unsigned)&PIE3*8)+2;
extern          near bit	TMR4IE		@ ((unsigned)&PIE3*8)+3;
extern          near bit	TX2IE		@ ((unsigned)&PIE3*8)+4;
extern          near bit	RC2IE		@ ((unsigned)&PIE3*8)+5;

/* Definitions for IPR2 register */
extern          near bit	CCP2IP		@ ((unsigned)&IPR2*8)+0;
extern          near bit	TMR3IP		@ ((unsigned)&IPR2*8)+1;
extern          near bit	LVDIP		@ ((unsigned)&IPR2*8)+2;
extern          near bit	BCLIP		@ ((unsigned)&IPR2*8)+3;
extern          near bit	EEIP		@ ((unsigned)&IPR2*8)+4;
extern          near bit	CMIP		@ ((unsigned)&IPR2*8)+6;

/* Definitions for PIR2 register */
extern volatile near bit	CCP2IF		@ ((unsigned)&PIR2*8)+0;
extern volatile near bit	TMR3IF		@ ((unsigned)&PIR2*8)+1;
extern volatile near bit	LVDIF		@ ((unsigned)&PIR2*8)+2;
extern volatile near bit	BCLIF		@ ((unsigned)&PIR2*8)+3;
extern volatile near bit	EEIF		@ ((unsigned)&PIR2*8)+4;
extern volatile near bit	CMIF		@ ((unsigned)&PIR2*8)+6;

/* Definitions for PIE2 register */
extern          near bit	CCP2IE		@ ((unsigned)&PIE2*8)+0;
extern          near bit	TMR3IE		@ ((unsigned)&PIE2*8)+1;
extern          near bit	LVDIE		@ ((unsigned)&PIE2*8)+2;
extern          near bit	BCLIE		@ ((unsigned)&PIE2*8)+3;
extern          near bit	EEIE		@ ((unsigned)&PIE2*8)+4;
extern          near bit	CMIE		@ ((unsigned)&PIE2*8)+6;

/* Definitions for IPR1 register */
extern          near bit	TMR1IP		@ ((unsigned)&IPR1*8)+0;
extern          near bit	TMR2IP		@ ((unsigned)&IPR1*8)+1;
extern          near bit	CCP1IP		@ ((unsigned)&IPR1*8)+2;
extern          near bit	SSPIP		@ ((unsigned)&IPR1*8)+3;
extern          near bit	TX1IP		@ ((unsigned)&IPR1*8)+4;
extern          near bit	RC1IP		@ ((unsigned)&IPR1*8)+5;
extern          near bit	ADIP		@ ((unsigned)&IPR1*8)+6;
extern          near bit	PSPIP		@ ((unsigned)&IPR1*8)+7;
// Alternate definitions for compatibility with mono USART devices
extern 	near bit 	TXIP		@ ((unsigned)&IPR1*8)+4;	// USART TX interrupt priority
extern 	near bit 	RCIP		@ ((unsigned)&IPR1*8)+5;	// USART RX interrupt priority

/* Definitions for PIR1 register */
extern volatile near bit	TMR1IF		@ ((unsigned)&PIR1*8)+0;
extern volatile near bit	TMR2IF		@ ((unsigned)&PIR1*8)+1;
extern volatile near bit	CCP1IF		@ ((unsigned)&PIR1*8)+2;
extern volatile near bit	SSPIF		@ ((unsigned)&PIR1*8)+3;
extern volatile near bit	TX1IF		@ ((unsigned)&PIR1*8)+4;
extern volatile near bit	RC1IF		@ ((unsigned)&PIR1*8)+5;
extern volatile near bit	ADIF		@ ((unsigned)&PIR1*8)+6;
extern volatile near bit	PSPIF		@ ((unsigned)&PIR1*8)+7;
// Alternate definitions for compatibility with mono USART devices
extern volatile	near bit	TXIF  		@ ((unsigned)&PIR1*8)+4;	// USART TX interrupt flag
extern volatile	near bit	RCIF  		@ ((unsigned)&PIR1*8)+5;	// USART RX interrupt flag

/* Definitions for PIE1 register */
extern          near bit	TMR1IE		@ ((unsigned)&PIE1*8)+0;
extern          near bit	TMR2IE		@ ((unsigned)&PIE1*8)+1;
extern          near bit	CCP1IE		@ ((unsigned)&PIE1*8)+2;
extern          near bit	SSPIE		@ ((unsigned)&PIE1*8)+3;
extern          near bit	TX1IE		@ ((unsigned)&PIE1*8)+4;
extern          near bit	RC1IE		@ ((unsigned)&PIE1*8)+5;
extern          near bit	ADIE		@ ((unsigned)&PIE1*8)+6;
extern          near bit	PSPIE		@ ((unsigned)&PIE1*8)+7;
// Alternate definitions for compatibility with mono USART devices
extern 	near bit 	TXIE  		@ ((unsigned)&PIE1*8)+4;	// USART TX interrupt enable
extern 	near bit 	RCIE  		@ ((unsigned)&PIE1*8)+5;	// USART RX interrupt enable

#ifndef _18F6X2X
/* Definitions for MEMCON register */
extern          near bit	WM0		@ ((unsigned)&MEMCON*8)+0;
extern          near bit	WM1		@ ((unsigned)&MEMCON*8)+1;
extern          near bit	WAIT0		@ ((unsigned)&MEMCON*8)+4;
extern          near bit	WAIT1		@ ((unsigned)&MEMCON*8)+5;
extern          near bit	EBDIS		@ ((unsigned)&MEMCON*8)+7;

/* Definitions for TRISJ register */
extern volatile near bit	TRISJ0		@ ((unsigned)&TRISJ*8)+0;
extern volatile near bit	TRISJ1		@ ((unsigned)&TRISJ*8)+1;
extern volatile near bit	TRISJ2		@ ((unsigned)&TRISJ*8)+2;
extern volatile near bit	TRISJ3		@ ((unsigned)&TRISJ*8)+3;
extern volatile near bit	TRISJ4		@ ((unsigned)&TRISJ*8)+4;
extern volatile near bit	TRISJ5		@ ((unsigned)&TRISJ*8)+5;
extern volatile near bit	TRISJ6		@ ((unsigned)&TRISJ*8)+6;
extern volatile near bit	TRISJ7		@ ((unsigned)&TRISJ*8)+7;

/* Definitions for TRISH register */
extern volatile near bit	TRISH0		@ ((unsigned)&TRISH*8)+0;
extern volatile near bit	TRISH1		@ ((unsigned)&TRISH*8)+1;
extern volatile near bit	TRISH2		@ ((unsigned)&TRISH*8)+2;
extern volatile near bit	TRISH3		@ ((unsigned)&TRISH*8)+3;
extern volatile near bit	TRISH4		@ ((unsigned)&TRISH*8)+4;
extern volatile near bit	TRISH5		@ ((unsigned)&TRISH*8)+5;
extern volatile near bit	TRISH6		@ ((unsigned)&TRISH*8)+6;
extern volatile near bit	TRISH7		@ ((unsigned)&TRISH*8)+7;
#endif

/* Definitions for TRISG register */
extern volatile near bit	TRISG0		@ ((unsigned)&TRISG*8)+0;
extern volatile near bit	TRISG1		@ ((unsigned)&TRISG*8)+1;
extern volatile near bit	TRISG2		@ ((unsigned)&TRISG*8)+2;
extern volatile near bit	TRISG3		@ ((unsigned)&TRISG*8)+3;
extern volatile near bit	TRISG4		@ ((unsigned)&TRISG*8)+4;

/* Definitions for TRISF register */
extern volatile near bit	TRISF0		@ ((unsigned)&TRISF*8)+0;
extern volatile near bit	TRISF1		@ ((unsigned)&TRISF*8)+1;
extern volatile near bit	TRISF2		@ ((unsigned)&TRISF*8)+2;
extern volatile near bit	TRISF3		@ ((unsigned)&TRISF*8)+3;
extern volatile near bit	TRISF4		@ ((unsigned)&TRISF*8)+4;
extern volatile near bit	TRISF5		@ ((unsigned)&TRISF*8)+5;
extern volatile near bit	TRISF6		@ ((unsigned)&TRISF*8)+6;
extern volatile near bit	TRISF7		@ ((unsigned)&TRISF*8)+7;

/* Definitions for TRISE register */
extern volatile near bit	TRISE0		@ ((unsigned)&TRISE*8)+0;
extern volatile near bit	TRISE1		@ ((unsigned)&TRISE*8)+1;
extern volatile near bit	TRISE2		@ ((unsigned)&TRISE*8)+2;
extern volatile near bit	TRISE3		@ ((unsigned)&TRISE*8)+3;
extern volatile near bit	TRISE4		@ ((unsigned)&TRISE*8)+4;
extern volatile near bit	TRISE5		@ ((unsigned)&TRISE*8)+5;
extern volatile near bit	TRISE6		@ ((unsigned)&TRISE*8)+6;
extern volatile near bit	TRISE7		@ ((unsigned)&TRISE*8)+7;

/* Definitions for TRISD register */
extern volatile near bit	TRISD0		@ ((unsigned)&TRISD*8)+0;
extern volatile near bit	TRISD1		@ ((unsigned)&TRISD*8)+1;
extern volatile near bit	TRISD2		@ ((unsigned)&TRISD*8)+2;
extern volatile near bit	TRISD3		@ ((unsigned)&TRISD*8)+3;
extern volatile near bit	TRISD4		@ ((unsigned)&TRISD*8)+4;
extern volatile near bit	TRISD5		@ ((unsigned)&TRISD*8)+5;
extern volatile near bit	TRISD6		@ ((unsigned)&TRISD*8)+6;
extern volatile near bit	TRISD7		@ ((unsigned)&TRISD*8)+7;

/* Definitions for TRISC register */
extern volatile near bit	TRISC0		@ ((unsigned)&TRISC*8)+0;
extern volatile near bit	TRISC1		@ ((unsigned)&TRISC*8)+1;
extern volatile near bit	TRISC2		@ ((unsigned)&TRISC*8)+2;
extern volatile near bit	TRISC3		@ ((unsigned)&TRISC*8)+3;
extern volatile near bit	TRISC4		@ ((unsigned)&TRISC*8)+4;
extern volatile near bit	TRISC5		@ ((unsigned)&TRISC*8)+5;
extern volatile near bit	TRISC6		@ ((unsigned)&TRISC*8)+6;
extern volatile near bit	TRISC7		@ ((unsigned)&TRISC*8)+7;

/* Definitions for TRISB register */
extern volatile near bit	TRISB0		@ ((unsigned)&TRISB*8)+0;
extern volatile near bit	TRISB1		@ ((unsigned)&TRISB*8)+1;
extern volatile near bit	TRISB2		@ ((unsigned)&TRISB*8)+2;
extern volatile near bit	TRISB3		@ ((unsigned)&TRISB*8)+3;
extern volatile near bit	TRISB4		@ ((unsigned)&TRISB*8)+4;
extern volatile near bit	TRISB5		@ ((unsigned)&TRISB*8)+5;
extern volatile near bit	TRISB6		@ ((unsigned)&TRISB*8)+6;
extern volatile near bit	TRISB7		@ ((unsigned)&TRISB*8)+7;

/* Definitions for TRISA register */
extern volatile near bit	TRISA0		@ ((unsigned)&TRISA*8)+0;
extern volatile near bit	TRISA1		@ ((unsigned)&TRISA*8)+1;
extern volatile near bit	TRISA2		@ ((unsigned)&TRISA*8)+2;
extern volatile near bit	TRISA3		@ ((unsigned)&TRISA*8)+3;
extern volatile near bit	TRISA4		@ ((unsigned)&TRISA*8)+4;
extern volatile near bit	TRISA5		@ ((unsigned)&TRISA*8)+5;
extern volatile near bit	TRISA6		@ ((unsigned)&TRISA*8)+6;

#ifndef _18F6X2X
/* Definitions for LATJ register */
extern volatile near bit	LATJ0		@ ((unsigned)&LATJ*8)+0;
extern volatile near bit	LATJ1		@ ((unsigned)&LATJ*8)+1;
extern volatile near bit	LATJ2		@ ((unsigned)&LATJ*8)+2;
extern volatile near bit	LATJ3		@ ((unsigned)&LATJ*8)+3;
extern volatile near bit	LATJ4		@ ((unsigned)&LATJ*8)+4;
extern volatile near bit	LATJ5		@ ((unsigned)&LATJ*8)+5;
extern volatile near bit	LATJ6		@ ((unsigned)&LATJ*8)+6;
extern volatile near bit	LATJ7		@ ((unsigned)&LATJ*8)+7;

/* Definitions for LATH register */
extern volatile near bit	LATH0		@ ((unsigned)&LATH*8)+0;
extern volatile near bit	LATH1		@ ((unsigned)&LATH*8)+1;
extern volatile near bit	LATH2		@ ((unsigned)&LATH*8)+2;
extern volatile near bit	LATH3		@ ((unsigned)&LATH*8)+3;
extern volatile near bit	LATH4		@ ((unsigned)&LATH*8)+4;
extern volatile near bit	LATH5		@ ((unsigned)&LATH*8)+5;
extern volatile near bit	LATH6		@ ((unsigned)&LATH*8)+6;
extern volatile near bit	LATH7		@ ((unsigned)&LATH*8)+7;
#endif

/* Definitions for LATG register */
extern volatile near bit	LATG0		@ ((unsigned)&LATG*8)+0;
extern volatile near bit	LATG1		@ ((unsigned)&LATG*8)+1;
extern volatile near bit	LATG2		@ ((unsigned)&LATG*8)+2;
extern volatile near bit	LATG3		@ ((unsigned)&LATG*8)+3;
extern volatile near bit	LATG4		@ ((unsigned)&LATG*8)+4;

/* Definitions for LATF register */
extern volatile near bit	LATF0		@ ((unsigned)&LATF*8)+0;
extern volatile near bit	LATF1		@ ((unsigned)&LATF*8)+1;
extern volatile near bit	LATF2		@ ((unsigned)&LATF*8)+2;
extern volatile near bit	LATF3		@ ((unsigned)&LATF*8)+3;
extern volatile near bit	LATF4		@ ((unsigned)&LATF*8)+4;
extern volatile near bit	LATF5		@ ((unsigned)&LATF*8)+5;
extern volatile near bit	LATF6		@ ((unsigned)&LATF*8)+6;
extern volatile near bit	LATF7		@ ((unsigned)&LATF*8)+7;

/* Definitions for LATE register */
extern volatile near bit	LATE0		@ ((unsigned)&LATE*8)+0;
extern volatile near bit	LATE1		@ ((unsigned)&LATE*8)+1;
extern volatile near bit	LATE2		@ ((unsigned)&LATE*8)+2;
extern volatile near bit	LATE3		@ ((unsigned)&LATE*8)+3;
extern volatile near bit	LATE4		@ ((unsigned)&LATE*8)+4;
extern volatile near bit	LATE5		@ ((unsigned)&LATE*8)+5;
extern volatile near bit	LATE6		@ ((unsigned)&LATE*8)+6;
extern volatile near bit	LATE7		@ ((unsigned)&LATE*8)+7;

/* Definitions for LATD register */
extern volatile near bit	LATD0		@ ((unsigned)&LATD*8)+0;
extern volatile near bit	LATD1		@ ((unsigned)&LATD*8)+1;
extern volatile near bit	LATD2		@ ((unsigned)&LATD*8)+2;
extern volatile near bit	LATD3		@ ((unsigned)&LATD*8)+3;
extern volatile near bit	LATD4		@ ((unsigned)&LATD*8)+4;
extern volatile near bit	LATD5		@ ((unsigned)&LATD*8)+5;
extern volatile near bit	LATD6		@ ((unsigned)&LATD*8)+6;
extern volatile near bit	LATD7		@ ((unsigned)&LATD*8)+7;

/* Definitions for LATC register */
extern volatile near bit	LATC0		@ ((unsigned)&LATC*8)+0;
extern volatile near bit	LATC1		@ ((unsigned)&LATC*8)+1;
extern volatile near bit	LATC2		@ ((unsigned)&LATC*8)+2;
extern volatile near bit	LATC3		@ ((unsigned)&LATC*8)+3;
extern volatile near bit	LATC4		@ ((unsigned)&LATC*8)+4;
extern volatile near bit	LATC5		@ ((unsigned)&LATC*8)+5;
extern volatile near bit	LATC6		@ ((unsigned)&LATC*8)+6;
extern volatile near bit	LATC7		@ ((unsigned)&LATC*8)+7;

/* Definitions for LATB register */
extern volatile near bit	LATB0		@ ((unsigned)&LATB*8)+0;
extern volatile near bit	LATB1		@ ((unsigned)&LATB*8)+1;
extern volatile near bit	LATB2		@ ((unsigned)&LATB*8)+2;
extern volatile near bit	LATB3		@ ((unsigned)&LATB*8)+3;
extern volatile near bit	LATB4		@ ((unsigned)&LATB*8)+4;
extern volatile near bit	LATB5		@ ((unsigned)&LATB*8)+5;
extern volatile near bit	LATB6		@ ((unsigned)&LATB*8)+6;
extern volatile near bit	LATB7		@ ((unsigned)&LATB*8)+7;

/* Definitions for LATA register */
extern volatile near bit	LATA0		@ ((unsigned)&LATA*8)+0;
extern volatile near bit	LATA1		@ ((unsigned)&LATA*8)+1;
extern volatile near bit	LATA2		@ ((unsigned)&LATA*8)+2;
extern volatile near bit	LATA3		@ ((unsigned)&LATA*8)+3;
extern volatile near bit	LATA4		@ ((unsigned)&LATA*8)+4;
extern volatile near bit	LATA5		@ ((unsigned)&LATA*8)+5;
extern volatile near bit	LATA6		@ ((unsigned)&LATA*8)+6;

#ifndef _18F6X2X
/* Definitions for PORTJ register */
extern volatile near bit	RJ0		@ ((unsigned)&PORTJ*8)+0;
extern volatile near bit	RJ1		@ ((unsigned)&PORTJ*8)+1;
extern volatile near bit	RJ2		@ ((unsigned)&PORTJ*8)+2;
extern volatile near bit	RJ3		@ ((unsigned)&PORTJ*8)+3;
extern volatile near bit	RJ4		@ ((unsigned)&PORTJ*8)+4;
extern volatile near bit	RJ5		@ ((unsigned)&PORTJ*8)+5;
extern volatile near bit	RJ6		@ ((unsigned)&PORTJ*8)+6;
extern volatile near bit	RJ7		@ ((unsigned)&PORTJ*8)+7;

/* Definitions for PORTH register */
extern volatile near bit	RH0		@ ((unsigned)&PORTH*8)+0;
extern volatile near bit	RH1		@ ((unsigned)&PORTH*8)+1;
extern volatile near bit	RH2		@ ((unsigned)&PORTH*8)+2;
extern volatile near bit	RH3		@ ((unsigned)&PORTH*8)+3;
extern volatile near bit	RH4		@ ((unsigned)&PORTH*8)+4;
extern volatile near bit	RH5		@ ((unsigned)&PORTH*8)+5;
extern volatile near bit	RH6		@ ((unsigned)&PORTH*8)+6;
extern volatile near bit	RH7		@ ((unsigned)&PORTH*8)+7;
#endif

/* Definitions for PORTG register */
extern volatile near bit	RG0		@ ((unsigned)&PORTG*8)+0;
extern volatile near bit	RG1		@ ((unsigned)&PORTG*8)+1;
extern volatile near bit	RG2		@ ((unsigned)&PORTG*8)+2;
extern volatile near bit	RG3		@ ((unsigned)&PORTG*8)+3;
extern volatile near bit	RG4		@ ((unsigned)&PORTG*8)+4;
extern volatile near bit	RG5		@ ((unsigned)&PORTG*8)+5;

/* Definitions for PORTF register */
extern volatile near bit	RF0		@ ((unsigned)&PORTF*8)+0;
extern volatile near bit	RF1		@ ((unsigned)&PORTF*8)+1;
extern volatile near bit	RF2		@ ((unsigned)&PORTF*8)+2;
extern volatile near bit	RF3		@ ((unsigned)&PORTF*8)+3;
extern volatile near bit	RF4		@ ((unsigned)&PORTF*8)+4;
extern volatile near bit	RF5		@ ((unsigned)&PORTF*8)+5;
extern volatile near bit	RF6		@ ((unsigned)&PORTF*8)+6;
extern volatile near bit	RF7		@ ((unsigned)&PORTF*8)+7;

/* Definitions for PORTE register */
extern volatile near bit	RE0		@ ((unsigned)&PORTE*8)+0;
extern volatile near bit	RE1		@ ((unsigned)&PORTE*8)+1;
extern volatile near bit	RE2		@ ((unsigned)&PORTE*8)+2;
extern volatile near bit	RE3		@ ((unsigned)&PORTE*8)+3;
extern volatile near bit	RE4		@ ((unsigned)&PORTE*8)+4;
extern volatile near bit	RE5		@ ((unsigned)&PORTE*8)+5;
extern volatile near bit	RE6		@ ((unsigned)&PORTE*8)+6;
extern volatile near bit	RE7		@ ((unsigned)&PORTE*8)+7;

/* Definitions for PORTD register */
extern volatile near bit	RD0		@ ((unsigned)&PORTD*8)+0;
extern volatile near bit	RD1		@ ((unsigned)&PORTD*8)+1;
extern volatile near bit	RD2		@ ((unsigned)&PORTD*8)+2;
extern volatile near bit	RD3		@ ((unsigned)&PORTD*8)+3;
extern volatile near bit	RD4		@ ((unsigned)&PORTD*8)+4;
extern volatile near bit	RD5		@ ((unsigned)&PORTD*8)+5;
extern volatile near bit	RD6		@ ((unsigned)&PORTD*8)+6;
extern volatile near bit	RD7		@ ((unsigned)&PORTD*8)+7;

/* Definitions for PORTC register */
extern volatile near bit	RC0		@ ((unsigned)&PORTC*8)+0;
extern volatile near bit	RC1		@ ((unsigned)&PORTC*8)+1;
extern volatile near bit	RC2		@ ((unsigned)&PORTC*8)+2;
extern volatile near bit	RC3		@ ((unsigned)&PORTC*8)+3;
extern volatile near bit	RC4		@ ((unsigned)&PORTC*8)+4;
extern volatile near bit	RC5		@ ((unsigned)&PORTC*8)+5;
extern volatile near bit	RC6		@ ((unsigned)&PORTC*8)+6;
extern volatile near bit	RC7		@ ((unsigned)&PORTC*8)+7;

/* Definitions for PORTB register */
extern volatile near bit	RB0		@ ((unsigned)&PORTB*8)+0;
extern volatile near bit	RB1		@ ((unsigned)&PORTB*8)+1;
extern volatile near bit	RB2		@ ((unsigned)&PORTB*8)+2;
extern volatile near bit	RB3		@ ((unsigned)&PORTB*8)+3;
extern volatile near bit	RB4		@ ((unsigned)&PORTB*8)+4;
extern volatile near bit	RB5		@ ((unsigned)&PORTB*8)+5;
extern volatile near bit	RB6		@ ((unsigned)&PORTB*8)+6;
extern volatile near bit	RB7		@ ((unsigned)&PORTB*8)+7;

/* Definitions for PORTA register */
extern volatile near bit	RA0		@ ((unsigned)&PORTA*8)+0;
extern volatile near bit	RA1		@ ((unsigned)&PORTA*8)+1;
extern volatile near bit	RA2		@ ((unsigned)&PORTA*8)+2;
extern volatile near bit	RA3		@ ((unsigned)&PORTA*8)+3;
extern volatile near bit	RA4		@ ((unsigned)&PORTA*8)+4;
extern volatile near bit	RA5		@ ((unsigned)&PORTA*8)+5;
extern volatile near bit	RA6		@ ((unsigned)&PORTA*8)+6;

/* Definitions for BAUDCON register */
extern volatile near bit	ABDEN		@ ((unsigned)&BAUDCON*8)+0;
extern volatile near bit	WUE		@ ((unsigned)&BAUDCON*8)+1;
extern          near bit	BRG16		@ ((unsigned)&BAUDCON*8)+3;
extern volatile near bit	SCKP		@ ((unsigned)&BAUDCON*8)+4;
extern volatile near bit	RCIDL		@ ((unsigned)&BAUDCON*8)+6;

/* Definitions for BAUDCON2 register */
extern volatile near bit	ABDEN2		@ ((unsigned)&BAUDCON2*8)+0;
extern volatile near bit	WUE2		@ ((unsigned)&BAUDCON2*8)+1;
extern          near bit	BRG162		@ ((unsigned)&BAUDCON2*8)+3;
extern volatile near bit	SCKP2		@ ((unsigned)&BAUDCON2*8)+4;
extern volatile near bit	RCIDL2		@ ((unsigned)&BAUDCON2*8)+6;

/* Definitions for ECCP1DEL register */
extern          near bit	P1DC0		@ ((unsigned)&ECCP1DEL*8)+0;
extern          near bit	P1DC1		@ ((unsigned)&ECCP1DEL*8)+1;
extern          near bit	P1DC2		@ ((unsigned)&ECCP1DEL*8)+2;
extern          near bit	P1DC3		@ ((unsigned)&ECCP1DEL*8)+3;
extern          near bit	P1DC4		@ ((unsigned)&ECCP1DEL*8)+4;
extern          near bit	P1DC5		@ ((unsigned)&ECCP1DEL*8)+5;
extern          near bit	P1DC6		@ ((unsigned)&ECCP1DEL*8)+6;
extern          near bit	P1RSEN		@ ((unsigned)&ECCP1DEL*8)+7;

/* Definitions for T4CON register */
extern          near bit	T4CKPS0		@ ((unsigned)&T4CON*8)+0;
extern          near bit	T4CKPS1		@ ((unsigned)&T4CON*8)+1;
extern          near bit	TMR4ON		@ ((unsigned)&T4CON*8)+2;
extern          near bit	TOUTPS0		@ ((unsigned)&T4CON*8)+3;
extern          near bit	TOUTPS1		@ ((unsigned)&T4CON*8)+4;
extern          near bit	TOUTPS2		@ ((unsigned)&T4CON*8)+5;
extern          near bit	TOUTPS3		@ ((unsigned)&T4CON*8)+6;

/* Definitions for CCP4CON register */
extern          near bit	CCP4M0		@ ((unsigned)&CCP4CON*8)+0;
extern          near bit	CCP4M1		@ ((unsigned)&CCP4CON*8)+1;
extern          near bit	CCP4M2		@ ((unsigned)&CCP4CON*8)+2;
extern          near bit	CCP4M3		@ ((unsigned)&CCP4CON*8)+3;
extern volatile near bit	CCP4Y		@ ((unsigned)&CCP4CON*8)+4;
extern volatile near bit	CCP4X		@ ((unsigned)&CCP4CON*8)+5;

/* Alternate definitions for CCP4CON register for compatibilty*/
extern          near bit	DC4B0		@ ((unsigned)&CCP4CON*8)+4;
extern          near bit	DC4B1		@ ((unsigned)&CCP4CON*8)+5;

/* Definitions for CCP5CON register */
extern          near bit	CCP5M0		@ ((unsigned)&CCP5CON*8)+0;
extern          near bit	CCP5M1		@ ((unsigned)&CCP5CON*8)+1;
extern          near bit	CCP5M2		@ ((unsigned)&CCP5CON*8)+2;
extern          near bit	CCP5M3		@ ((unsigned)&CCP5CON*8)+3;
extern volatile near bit	CCP5Y		@ ((unsigned)&CCP5CON*8)+4;
extern volatile near bit	CCP5X		@ ((unsigned)&CCP5CON*8)+5;

/* Alternate definitions for CCP5CON register for compatibilty*/
extern          near bit	DC5B0		@ ((unsigned)&CCP5CON*8)+4;
extern          near bit	DC5B1		@ ((unsigned)&CCP5CON*8)+5;

/* Definitions for TXSTA2 register */
extern volatile near bit	TX9D2		@ ((unsigned)&TXSTA2*8)+0;
extern volatile near bit	TRMT2		@ ((unsigned)&TXSTA2*8)+1;
extern          near bit	BRGH2		@ ((unsigned)&TXSTA2*8)+2;
extern          near bit	SENDB2		@ ((unsigned)&TXSTA2*8)+3;
extern          near bit	SYNC2		@ ((unsigned)&TXSTA2*8)+4;
extern          near bit	TXEN2		@ ((unsigned)&TXSTA2*8)+5;
extern          near bit	TX92		@ ((unsigned)&TXSTA2*8)+6;
extern          near bit	CSRC2		@ ((unsigned)&TXSTA2*8)+7;

/* Definitions for RCSTA2 register */
extern volatile near bit	RX9D2		@ ((unsigned)&RCSTA2*8)+0;
extern volatile near bit	OERR2		@ ((unsigned)&RCSTA2*8)+1;
extern volatile near bit	FERR2		@ ((unsigned)&RCSTA2*8)+2;
extern          near bit	ADEN2		@ ((unsigned)&RCSTA2*8)+3;
extern          near bit	CREN2		@ ((unsigned)&RCSTA2*8)+4;
extern          near bit	SREN2		@ ((unsigned)&RCSTA2*8)+5;
extern          near bit	RX92		@ ((unsigned)&RCSTA2*8)+6;
extern          near bit	SPEN2		@ ((unsigned)&RCSTA2*8)+7;

/* Definitions for ECCP3AS register */
extern          near bit	PSS3BD0		@ ((unsigned)&ECCP3AS*8)+0;
extern          near bit	PSS3BD1		@ ((unsigned)&ECCP3AS*8)+1;
extern          near bit	PSS3AC0		@ ((unsigned)&ECCP3AS*8)+2;
extern          near bit	PSS3AC1		@ ((unsigned)&ECCP3AS*8)+3;
extern          near bit	ECCP3AS0	@ ((unsigned)&ECCP3AS*8)+4;
extern          near bit	ECCP3AS1	@ ((unsigned)&ECCP3AS*8)+5;
extern          near bit	ECCP3AS2	@ ((unsigned)&ECCP3AS*8)+6;
extern volatile near bit	ECCP3ASE	@ ((unsigned)&ECCP3AS*8)+7;

/* Definitions for ECCP3DEL register */
extern          near bit	P3DC0		@ ((unsigned)&ECCP3DEL*8)+0;
extern          near bit	P3DC1		@ ((unsigned)&ECCP3DEL*8)+1;
extern          near bit	P3DC2		@ ((unsigned)&ECCP3DEL*8)+2;
extern          near bit	P3DC3		@ ((unsigned)&ECCP3DEL*8)+3;
extern          near bit	P3DC4		@ ((unsigned)&ECCP3DEL*8)+4;
extern          near bit	P3DC5		@ ((unsigned)&ECCP3DEL*8)+5;
extern          near bit	P3DC6		@ ((unsigned)&ECCP3DEL*8)+6;
extern          near bit	P3RSEN		@ ((unsigned)&ECCP3DEL*8)+7;

/* Definitions for ECCP2AS register */
extern          near bit	PSS2BD0		@ ((unsigned)&ECCP2AS*8)+0;
extern          near bit	PSS2BD1		@ ((unsigned)&ECCP2AS*8)+1;
extern          near bit	PSS2AC0		@ ((unsigned)&ECCP2AS*8)+2;
extern          near bit	PSS2AC1		@ ((unsigned)&ECCP2AS*8)+3;
extern          near bit	ECCP2AS0	@ ((unsigned)&ECCP2AS*8)+4;
extern          near bit	ECCP2AS1	@ ((unsigned)&ECCP2AS*8)+5;
extern          near bit	ECCP2AS2	@ ((unsigned)&ECCP2AS*8)+6;
extern volatile near bit	ECCP2ASE	@ ((unsigned)&ECCP2AS*8)+7;

/* Definitions for ECCP2DEL register */
extern          near bit	P2DC0		@ ((unsigned)&ECCP2DEL*8)+0;
extern          near bit	P2DC1		@ ((unsigned)&ECCP2DEL*8)+1;
extern          near bit	P2DC2		@ ((unsigned)&ECCP2DEL*8)+2;
extern          near bit	P2DC3		@ ((unsigned)&ECCP2DEL*8)+3;
extern          near bit	P2DC4		@ ((unsigned)&ECCP2DEL*8)+4;
extern          near bit	P2DC5		@ ((unsigned)&ECCP2DEL*8)+5;
extern          near bit	P2DC6		@ ((unsigned)&ECCP2DEL*8)+6;
extern          near bit	P2RSEN		@ ((unsigned)&ECCP2DEL*8)+7;


#define EEPROM_SIZE 1024

#if defined(_18FX525)
#define ROMSIZE 49152
#else
#define ROMSIZE 65536
#endif

// Configuration Bit Values

// Configuration register 1
 #define OSCSEN		0xDFFF 	// enable oscillator system clock switch 
 #define OSCSDIS	0xFFFF 
 #define RCIO		0xFFFF 	// RC RA6=OSC2 
 #define RCRA6		RCIO 	// deprecated
 #define HSSW		0xFEFF 	// HS with SW 4xPLL 
 #define ECSW		0xFDFF 	// EC osc + SW 4xPLL 
 #define ECHW		0xFCFF 	// EC osc + HW 4xPLL 
 #define RC		0xF7FF 	// RC osc with RA6 
 #define HSHW		0xF6FF 	// HS osc + HW 4xPLL 
 #define EC		0xF5FF 	// EC with RA6 
 #define ECDB4		0xF4FF 	// EC with OSC2/4 
 #define RCDB4		0xF3FF 	// RC with OSC2/4 
 #define HS		0xF2FF 	// HS osc 
 #define XT		0xF1FF 	// XT osc 
 #define LP		0xF0FF 	// LP osc 

// Configuration register 2
 #define BOREN		0xFFFF 	// included only for completeness 
 #define BORDIS		0xFFFD 	// Brown out reset disabled 
 #define BORV45		0xFFF3 	// Brown out reset enabled, reset at 4.5V 
 #define BORV42		0xFFF7 	// Brown out reset enabled, reset at 4.2V 
 #define BORV27		0xFFFB 	// Brown out reset enabled, reset at 2.7V 
 #define BORV20		0xFFFF 	// Brown out reset enabled, reset at 2.5V 
 #define PWRTEN		0xFFFE 	// Power-up timer enable 
 #define PWRTDIS	0xFFFF 	// Power-up timer disable 
 #define WDTPS1		0xE1FF 	// Watchdog timer enabled with prescaler(s) 
 #define WDTPS2		0xE3FF 
 #define WDTPS4		0xE5FF 
 #define WDTPS8		0xE7FF 
 #define WDTPS16	0xE9FF 
 #define WDTPS32	0xEBFF 
 #define WDTPS64	0xEDFF 
 #define WDTPS128	0xEFFF 
 #define WDTPS256	0xF1FF 
 #define WDTPS512	0xF3FF 
 #define WDTPS1K	0xF5FF 
 #define WDTPS2K	0xF7FF 
 #define WDTPS4K	0xF9FF 
 #define WDTPS8K	0xFBFF 
 #define WDTPS16K	0xFDFF 
 #define WDTPS32K	0xFFFF 
 #define WDTDIS		0xFEFF 	// Watchdog timer disabled 
 #define WDTEN		0xFFFF 	// included only for completeness 

// Configuration register 3
#ifndef _18F6X2X
 #define WAITEN		0xFF7F 	// WAIT mode active & determined by WAIT1:WAIT0 bits 
 #define WAITDIS	0xFFFF 	// WAIT mode inactive 
 #define MCU		0xFFFF 	// select microcontroller mode 
 #define MPU		0xFFFE 	// select microprocessor mode 
 #define MPUBB		0xFFFD 	// select microprocessor mode with boot block mode 
 #define XMCU		0xFFFC 	// select extended microcontroller mode 
 #define ECCPRE		0xFFFF 	// ECCP1/3 multiplexed to RE6-3 
 #define ECCPRH		0xFDFF 	// ECCP1/3 multiplexed to RH7-4 
 #define CCP2RB3	0xFEFF 	// CCP2 multiplexed to RB3 
#endif
 #define MCLREN		0xFFFF 	// MCLR pin enabled 
 #define MCLRDIS	0x7FFF 	// Disable MCLR 
 #define CCP2RC1	0xFFFF 	// CCP2 multiplexed to RC1 
 #define CCP2RE7	0xFEFF 	// CCP2 multiplexed to RE7 

// Configuration register 4
 #define DEBUGEN	0xFF7F 	// Debugger enabled 
 #define DEBUGDIS	0xFFFF 	// Debugger disabled 
 #define LVPEN		0xFFFF 	// Low voltage ISP enabled 
 #define LVPDIS		0xFFFB 	// Low voltage ISP disabled 
 #define STVREN		0xFFFF 	// Stack over/underflow will cause reset 
 #define STVRDIS	0xFFFE 	// Stack over/underflow will not cause reset 

// Configuration register 5
 #define UNPROTECT	0xFFFF 	// Do not protect memory 
 #define CPA		0xFFF0 	// Protect program memory sections 
#ifndef _18FX525
 #define CP3		0xFFF7 	// Protect program memory block 3 
#endif
 #define CP2		0xFFFB 	// Protect program memory block 2 
 #define CP1		0xFFFD 	// Protect program memory block 1 
 #define CP0		0xFFFE 	// Protect program memory block 0 
 #define CPD		0x7FFF 	// Protect EEPROM data 
 #define CPB		0xBFFF 	// Protect boot block 
 #define CPALL		0x3FF0 	// Protect all of the above 

// Configuration register 6
 #define WRTEN		0xFFFF 	// Write enabled 
 #define WPA		0xFFF0 	// Write protect program memory sections 
#ifndef _18FX525
 #define WP3		0xFFF7 	// Write protect program memory block 3 
#endif
 #define WP2		0xFFFB 	// Write protect program memory block 2 
 #define WP1		0xFFFD 	// Write protect program memory block 1 
 #define WP0		0xFFFE 	// Write protect program memory block 0 
 #define WPD		0x7FFF 	// Write protect EEPROM data 
 #define WPB		0xBFFF 	// Write protect boot block 
 #define WPC		0xDFFF 	// Write protect configuration registers 
 #define WPALL		0x1FF0 	// Write protect all of the above 

// Configuration register 7
 #define TRPA		0xFFF0 	// Table read protect program memory sections 
#ifndef _18FX525
 #define TRP3		0xFFF7 	// Table read protect program memory block 3 
#endif
 #define TRP2		0xFFFB 	// Table read protect program memory block 2 
 #define TRP1		0xFFFD 	// Table read protect program memory block 1 
 #define TRP0		0xFFFE 	// Table read protect program memory block 0 
 #define TRPB		0xBFFF 	// Table read protect boot block 
 #define TRPALL		0xBFF0 	// Table read protect all of the above 

#endif
