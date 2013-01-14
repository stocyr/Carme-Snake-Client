/* general control */

/*****************************************************************************/
/*  Module     : SerialPortInterface                            Version 1.0  */
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
/*  File       : serport.c                                                   */
/*                                                                           */
/*****************************************************************************/
/* MagicSoft                                                                 */
/*****************************************************************************/

/* imports */
#include "serport.h"
#include <windows.h>

/* module constant declaration */

/* module type declaration */

/* module data declaration */
static HANDLE         ComPort;
static COMMTIMEOUTS   OldTimeout;

/* module procedure declaration */

/*****************************************************************************/
/*  Procedure   : InitSerialPort                                             */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Initializion for the serial interface. Opens the selected  */
/*                comunicationsport and prepares everything for communication*/
/*                                                                           */
/*  Type        : Global                                                     */
/*                                                                           */
/*  Input Para  : PortType Either COM1 or COM2                               */
/*                BaudRate Requested baudrate for communication              */
/*                Parity   Either NONE, EVEN, ODD, MARK or SPACE             */
/*                Bits     Number of Databits, either 7 or 8                 */
/*                StopBits Number of stopbits, either 1 or 2                 */
/*                                                                           */
/*  Output Para : 0 on success, negative Value otherwise                     */
/*                                                                           */
/*  Author      : I. Oesch                                                   */
/*                                                                           */
/*  History     : 12.07.2002  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/

int InitSerialPort(PortType Port, BaudrateType BaudRate, ParityType Parity,
					                int Bits, int Stopbits)
{
   /* Method data declaration      */
   char *PortId = "";
   COMMTIMEOUTS   NewTimeout = {0};
   DCB            DeviceControlBlock;

   /* Method code declaration      */

   /*check for correct port */
   switch (Port) {
      case COM1:
        PortId = "COM1";
	    break;

      case COM2 :
        PortId = "COM2";
	    break;

      case COM3 :
        PortId = "COM3";
        break;

      case COM4 :
        PortId = "COM4";
      	break;

      case COM5 :
        PortId = "COM5";
      	break;

      case COM6 :
        PortId = "COM6";
      	break;

      case COM7 :
        PortId = "COM7";
      	break;

      default:
	    return -1;
	    break;
   }

   /* Open the selected port */
   ComPort = CreateFile( PortId,
                         GENERIC_READ | GENERIC_WRITE,
                         0,
                         0,
                         OPEN_EXISTING,
                         0,
                         0);

   /* check if port could be openend */
   if(ComPort != INVALID_HANDLE_VALUE) {

      /* Set the comm timeouts such, that read returns immediately */
      /* independent if any bytes are availlable or not            */
      GetCommTimeouts(ComPort,&OldTimeout);
      NewTimeout.ReadIntervalTimeout = MAXDWORD;
      SetCommTimeouts(ComPort, &NewTimeout);

      /* Setup the device controlblock (Baudrate and other parameters) */
      DeviceControlBlock.DCBlength = sizeof(DCB);
      GetCommState(ComPort, &DeviceControlBlock);
      BuildCommDCB("baud=1200 parity=N data=8 stop=1", &DeviceControlBlock);
      switch (BaudRate) {
		case Bd600 :
           DeviceControlBlock.BaudRate = CBR_600;
		   break;

		case Bd1200 :
           DeviceControlBlock.BaudRate = CBR_1200;
		   break;

		case Bd2400 :
           DeviceControlBlock.BaudRate = CBR_2400;
	       break;

		case Bd4800 :
           DeviceControlBlock.BaudRate = CBR_4800;
	       break;

		case Bd9600 :
           DeviceControlBlock.BaudRate = CBR_9600;
	       break;

		case Bd19200 :
           DeviceControlBlock.BaudRate = CBR_19200;
	       break;

        default:
	       /* illegal baudrate... */
           ShutdownSerialPort();
	       return -2;
	       break;
      }
      switch (Bits) {
         case 5:
         case 6:
         case 7:
         case 8:
            DeviceControlBlock.ByteSize = Bits;
            break;

         default:
            ShutdownSerialPort();
	        return -3;
	        break;
      }
      switch (Stopbits) {
         case 1: DeviceControlBlock.StopBits = 0; break;  // 1 = 1.5
         case 2: DeviceControlBlock.StopBits = 2; break;
         default: ShutdownSerialPort(); return -4; break;
      }
      switch (Parity) {
         case P_NONE:  DeviceControlBlock.fParity = 0;
                     DeviceControlBlock.Parity  = 0;
                     break;
         case P_EVEN:  DeviceControlBlock.fParity = 1;
                     DeviceControlBlock.Parity  = 2;
                     break;
         case P_ODD:   DeviceControlBlock.fParity = 1;
                     DeviceControlBlock.Parity  = 1;
                     break;
         case P_MARK:  DeviceControlBlock.fParity = 1;
                     DeviceControlBlock.Parity  = 3;
                     break;
         case P_SPACE: DeviceControlBlock.fParity = 1;
                     DeviceControlBlock.Parity  = 4;
                     break;
         default:    ShutdownSerialPort();
                     return -5;
                     break;
      }
      SetCommState(ComPort, &DeviceControlBlock);
   }
   return 0;
}
/*****************************************************************************/
/*  End         : InitSerialPort                                             */
/*****************************************************************************/

/*****************************************************************************/
/*  Procedure   : ShutdownSerialPort                                         */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Stops all pending communications and closes the port       */
/*                                                                           */
/*  Type        : Global                                                     */
/*                                                                           */
/*  Input Para  : None                                                       */
/*                                                                           */
/*  Output Para : None                                                       */
/*                                                                           */
/*  Author      : I. Oesch                                                   */
/*                                                                           */
/*  History     : 12.07.2002  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
void ShutdownSerialPort(void)
{
   /* Method data declaration      */

   /* Method code declaration      */

   /* Abort any pending operations */
   PurgeComm(ComPort, PURGE_RXABORT);

   /* Restore old settings */
   SetCommTimeouts(ComPort, &OldTimeout);

   /* and close the port */
   CloseHandle(ComPort);
}
/*****************************************************************************/
/*  End         : ShutdownSerialPort                                         */
/*****************************************************************************/

/*****************************************************************************/
/*  Procedure   : GetByteFromSerialPort                                      */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Fetches a Byte from the inputbuffer                        */
/*                                                                           */
/*  Type        : Global                                                     */
/*                                                                           */
/*  Input Para  : None                                                       */
/*                                                                           */
/*  Output Para : Byte from Buffer or -1 if none availlable                  */
/*                                                                           */
/*  Author      : I. Oesch                                                   */
/*                                                                           */
/*  History     : 12.07.2002  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
int GetByteFromSerialPort(void)
{
   /* Method data declaration      */
   int Value = -1;
   unsigned char Buffer[10];
   DWORD BytesRead;

   /* Method code declaration      */

   /* Read one byte */
   ReadFile(ComPort, Buffer, 1, &BytesRead, NULL);

   /* Check if we got one, if not, return -1 */
   if (BytesRead > 0) {
      Value = Buffer[0];
   }
   return Value;
}
/*****************************************************************************/
/*  End         : GetByteFromSerialPort                                      */
/*****************************************************************************/

/*****************************************************************************/
/*  Procedure   : SendByteToSerialPort                                       */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Sends a Byte to the serial port                            */
/*                                                                           */
/*  Type        : Global                                                     */
/*                                                                           */
/*  Input Para  : Byte     Byte    to transmit                               */
/*                                                                           */
/*  Output Para : none                                                       */
/*                                                                           */
/*  Author      : I. Oesch                                                   */
/*                                                                           */
/*  History     : 12.07.2002  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
void SendByteToSerialPort(int Byte)
{
   /* Method data declaration      */
   char Buffer[10];
   DWORD BytesWroten;

   /* Method code declaration      */

   /* Write the Byte */
   Buffer[0] = Byte;
   WriteFile(ComPort, Buffer, 1, &BytesWroten, NULL);
}
/*****************************************************************************/
/*  End         : SendByteToSerialPort                                       */
/*****************************************************************************/

/*****************************************************************************/
/*  Procedure   : ClearSerialPortBuffer                                      */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Clears the receivebuffer                                   */
/*                                                                           */
/*  Type        : Global                                                     */
/*                                                                           */
/*  Input Para  : None                                                       */
/*                                                                           */
/*  Output Para : none                                                       */
/*                                                                           */
/*  Author      : I. Oesch                                                   */
/*                                                                           */
/*  History     : 12.07.2002  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
void ClearSerialPortBuffer(void)
{
   /* Method data declaration      */

   /* Method code declaration      */

   /* clear the transmit and the receivebuffer */
   PurgeComm(ComPort, PURGE_TXCLEAR|PURGE_RXCLEAR);
}
/*****************************************************************************/
/*  End         : ClearSerialPortBuffer                                      */
/*****************************************************************************/

/*****************************************************************************/
/*  Procedure   : BytesAvaillableFromSerialPort                              */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Returns the amount of availlable bytes in the receive      */
/*                buffer                                                     */
/*                                                                           */
/*  Type        : Global                                                     */
/*                                                                           */
/*  Input Para  : None                                                       */
/*                                                                           */
/*  Output Para : Number of Bytes availlable in Inputbuffer                  */
/*                                                                           */
/*  Author      : I. Oesch                                                   */
/*                                                                           */
/*  History     : 12.07.2002  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
int BytesAvaillableFromSerialPort(void)
{
   /* Method data declaration      */
   DWORD    Errors;	// pointer to variable to receive error codes
   COMSTAT  Stat;	// pointer to buffer for communications status

   /* Method code declaration      */
   /* get the comm state */
   ClearCommError(ComPort, &Errors, &Stat);

   return (Stat.cbInQue);        // bytes in input buffer
}
/*****************************************************************************/
/*  End         : BytesAvaillableFromSerialPort                              */
/*****************************************************************************/

/*****************************************************************************/
/*  Procedure   : UnsentBytesInSerialPort                                    */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Returns the number of bytes still to transmit in buffer    */
/*                                                                           */
/*  Type        : Global                                                     */
/*                                                                           */
/*  Input Para  : None                                                       */
/*                                                                           */
/*  Output Para : Number of Bytes stil waiting to be transmited              */
/*                                                                           */
/*  Author      : I. Oesch                                                   */
/*                                                                           */
/*  History     : 12.07.2002  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
int UnsentBytesInSerialPort(void)
{
   /* Method data declaration      */
   DWORD    Errors;	// pointer to variable to receive error codes
   COMSTAT  Stat;	// pointer to buffer for communications status

   /* Method code declaration      */
   /* get the comm state */
   ClearCommError(ComPort, &Errors, &Stat);

   return (Stat.cbOutQue);        // bytes in output buffer
}
/*****************************************************************************/
/*  End         : UnsentBytesInSerialPort                                    */
/*****************************************************************************/

/*****************************************************************************/
/*  End Module  : SerialPortInterface                                        */
/*****************************************************************************/

