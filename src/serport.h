#ifndef SERIAL_PORT_INTERFACE_H
#define SERIAL_PORT_INTERFACE_H
/*****************************************************************************/
/*  Header     : SerialPortInterface                            Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : This module is an interface to the win32 API-Functions to   */
/*               handle the serial port                                      */
/*                                                                           */
/*  Procedures : InitSerialPort                Initializes the serial port   */
/*               ShutdownSerialPort            Releases the serial port      */
/*               GetByteFromSerialPort         Reads a byte from serial port */
/*               SendByteToSerialPort          Sends a byte to the serial pt */
/*               ClearSerialPortBuffer         Empties the transmit buffer   */
/*               BytesAvaillableFromSerialPort Amount of availlable bytes    */
/*               UnsentBytesInSerialPort       How many bytes still to send  */
/*                                                                           */
/*  Author     : I. Oesch                                                    */
/*                                                                           */
/*  History    : 12.07.2002  IO Created                                      */
/*                                                                           */
/*  File       : serport.h                                                   */
/*                                                                           */
/*****************************************************************************/
/* MagicSoft                                                                 */
/*****************************************************************************/

/* imports */

/* module constant declaration  */

/* module type declaration      */
typedef enum PortType {
	DUMMY,
	COM1 = 1,
	COM2 = 2,
	COM3 = 3,
	COM4 = 4
} PortType;

typedef enum ParityType {
	P_NONE,
	P_EVEN,
	P_ODD,
	P_MARK,
	P_SPACE,
} ParityType;

typedef enum BaudrateType {
	Bd600,
	Bd1200,
	Bd2400,
	Bd4800,
	Bd9600,
	Bd19200
} BaudrateType;

/* module data declaration      */

/* module procedure declaration */
extern int  InitSerialPort(PortType Port, BaudrateType BaudRate, ParityType Parity, int Bits, int Stopbits);
extern void ShutdownSerialPort(void);
extern int  GetByteFromSerialPort(void);
extern void SendByteToSerialPort(int Byte);
extern void ClearSerialPortBuffer(void);
extern int  BytesAvaillableFromSerialPort(void);
extern int  UnsentBytesInSerialPort(void);

/*****************************************************************************/
/*  End Header  : SerialPortInterface                                        */
/*****************************************************************************/
#endif




