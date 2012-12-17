/*
 ============================================================================
 Name        : Carme-Snake-PC.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // for kbhit
#include "serport.h"

#define NO_VALID_KEY 	-1
#define KEY_UP			328
#define KEY_DOWN		336
#define KEY_LEFT		331
#define KEY_RIGHT		333

int getkey(void)
{
   int in;
   in = getch();
   //printf("in: %d\n",in);
   if (in == 0x00 || in == 0xe0)
   {
      return(getch()+0x100);
   }
   else
   {
      return NO_VALID_KEY;
   }
}


int main(int argc, char *argv[])
{
  int key, key_old, score, comport;
  char* argument;

  comport = COM4;

  printf("%d  %s  %s", argc, argv[0], argv[1]);

  if(argc == 2)
  {
	  // ein argument wurde mitgegeben -> COM port
	  argument = argv[1];

	  if(argument[0] >= '0' && argument[0] <= '9')
	  {
		  // wenn gültig
		  comport = argument[0] - '0';
	  }
  }


  if (InitSerialPort(comport, Bd9600, P_NONE, 8, 1) == 0)	// COM1
  {
     do
     {

        if(kbhit())	// Wenn Taste gedrückt
        {

        	key_old = key;			// Alter Wert speichern
        	key=getkey();

			switch(key)
			{
			case KEY_UP:
				key = 'u';
				break;
			case KEY_DOWN:
				key = 'd';
				break;
			case KEY_LEFT:
				key = 'l';
				break;
			case KEY_RIGHT:
				key = 'r';
				break;
			default:
				key = NO_VALID_KEY;
				break;
			}

			 if((key > 0) && (key != key_old))
			 {
				 //putc(key,stdout);
				 SendByteToSerialPort(key);

			 }

         }

        score = GetByteFromSerialPort();
     } while (score == -1);

     // Hier Score mit Highscore vergleichen und speichern

     ShutdownSerialPort();
  }
  system("pause");
  return EXIT_SUCCESS;
}
