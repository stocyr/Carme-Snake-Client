#include <stdio.h>
#include "serport.h"


int main_useless(int argc, char *argv[])
{
  int c;
  if (InitSerialPort(COM1, Bd2400, P_NONE, 8, 1) == 0) {
     do {
        c = GetByteFromSerialPort();
        if (c >= 0) {
           putchar(c);
        }
        c = getchar();
        SendByteToSerialPort(c);
     } while (c != 27);
     ShutdownSerialPort();
  }

  return 0;
}
