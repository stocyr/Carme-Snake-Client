/*****************************************************************************/
/*  Modul      :   Game                                         Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   :   Kommunikation mit dem Carme-Kit über die serielle Schnitt-*/
/*				   stelle, Start des Spiels und Verarbeitung des Scores		 */
/*                                                                           */
/*  Bearbeiter :   P. Ambuehl                                                */
/*                                                                           */
/*  History    :   24.12.2012 erstellt ambup1                                */
/*                                                                           */
/*  File Name  :   game.c                                                    */
/*                                                                           */
/*****************************************************************************/

/**
 *  \file game.c
 *  Modul game kommuniziert mit dem Serialport, liest Tastatureingaben ein und Ruft die Highscorefunktion auf
 */

// Files importieren
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>  // for kbhit
#include "highscore.h"
#include "game.h"
#include "window.h"
#include "serport.h"

#define NO_VALID_KEY 	-1
#define KEY_UP			328
#define KEY_DOWN		336
#define KEY_LEFT		331
#define KEY_RIGHT		333
#define EXIT			27

int getkey(void);

/*****************************************************************************/
/*  Funktion   : Game				                            Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   : Ruft die Modulfunktionen auf. Kommuniziert mit den          */
/* 				 übrigen Modulen.									         */
/*                                                                           */
/*  Bearbeiter : Peter Ambühl       	                                     */
/*                                                                           */
/*  History    : 24.12.2012 erstellt ambup1							         */
/*                                                                           */
/*****************************************************************************/


/**
 * Steuerung des eigentlichen Spiels.
 * Liest den Spielername ein, verabreitet die Steuerbefehle für die Schlange und den Score
 */

int Game(int argc, char* argv[], const char *ApplicationPath) {

	// Variabeln definieren
    char Name[20];		///< Array für Spielername
    int Zeichen;		///< Variable zur Verarbeitung der eingelesenen Zeichen
	int key;			///< Variable zum einlesen der Zeichen von der Tastatur
	int key_old;		///< Variable zum speichern des letzen eingelesenen Zeichens
	int score;			///< Variable für den Score
	int comport;		///< Variable für die Portnummer
	int winner;			///< Variable für Rückgabewert der Highscorefunktion
						///< Wird 1 wenn Highscore geknackt wurde, sonst 0
	char* argument;
	int i = 0;


	// Bildschirm löschen
	ClearWindow();

	// Spielernamen einlesen
	SelectFont("Arial MS", 15, FONT_NORMAL);
	DrawTextXY (50, 50, COL_GREEN, "Bitte Namen eingeben:");
	while((key = GetKeyPress()) != W_KEY_RETURN ){
		Zeichen = key;
		// Anzahl der Zeichen begrenzen, Leertaste unterdrücken
		if ((Zeichen >= ' ')&&(i < 19) && (Zeichen != 0x20) ){
			Name[i] = Zeichen;
			Name[i+1] = '\0';
			i++;
		}

		// Möglichkeit Zeichen zu löschen
		if( Zeichen == '\b'){
			if(i>0){
				i--;
				Name[i]='\0';
				DrawFilledRectangle(270, 25, 300, 40, COL_BLACK, 1);
			}
		}

		// Bisherige Eingabe anzeigen
		DrawTextXY (270, 50, COL_RED, Name);
	}
	ClearWindow();

	comport = COM4;

	printf("\nagruments: argc:%d  argv[0]:%s  argv[1]%s", argc, argv[0], argv[1]);

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
		 printf("\nPort opened: COM%d", comport);
		 do
	     {

			 if(kbhit())	// Wenn Taste gedrückt
			 {

	        	key_old = key;			// Alter Wert speichern
	        	key=getkey();

				switch(key)
				{
				case KEY_UP:
					if(key_old != KEY_DOWN)
					{
						key = 'u';
					}
					break;
				case KEY_DOWN:
					if(key_old != KEY_UP)
					{
						key = 'd';
					}
					break;
				case KEY_LEFT:
					if(key_old != KEY_RIGHT)
					{
						key = 'l';
					}
					break;
				case KEY_RIGHT:
					if(key_old != KEY_LEFT)
					{
						key = 'r';
					}
					break;
				case EXIT:
					break;
				default:
					key = NO_VALID_KEY;
					break;
				}
				// Nur wenn Key gültig ist und der Wert geändert hat ein Zeichen ans Carmekit senden
				if((key > 0) && (key != key_old))
				{
					 putc(key,stdout);
					 SendByteToSerialPort(key);

				}

	         }

	        score = GetByteFromSerialPort();
	     } while (score == -1);



	     ShutdownSerialPort();

	     winner=highscore(Name , score , ApplicationPath);
	     if(winner == 1)
	     {
	    	 DrawTextXY (220, 50, COL_GREEN, "! ! ! Du hast den High Score geknackt ! ! !");
	     }
	  }

	return 0;
}

/****************************************************************************/
/*	Ende Funktion Game      												*/
/****************************************************************************/

int getkey(void)
{
   int in;
   //in = getch();


   in = GetKeyPress();
   printf("in: %d\n",in);
   if (in == 0x00 || in == 0xe0)
   {
      return(getch()+0x100);
   }
   else
   {
      return NO_VALID_KEY;
   }
}

/*****************************************************************************/
/*  Ende Modul Game                                          				 */
/*****************************************************************************/
