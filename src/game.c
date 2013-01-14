/*****************************************************************************/
/*  Modul      :   Game                                         Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   :   Kommunikation mit dem Carme-Kit �ber die serielle Schnitt-*/
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
#include "highscore.h"
#include "game.h"
#include "window.h"
#include "serport.h"

#define NO_VALID_KEY 	-1

/*****************************************************************************/
/*  Funktion   : Game				                            Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   : Ruft die Modulfunktionen auf. Kommuniziert mit den          */
/* 				 �brigen Modulen.									         */
/*                                                                           */
/*  Bearbeiter : Peter Amb�hl       	                                     */
/*                                                                           */
/*  History    : 24.12.2012 erstellt ambup1							         */
/*                                                                           */
/*****************************************************************************/


/**
 * Steuerung des eigentlichen Spiels.
 * Liest den Spielername ein, verabreitet die Steuerbefehle f�r die Schlange und den Score
 */

int Game(int argc, char* argv[], const char *ApplicationPath) {

	// Variabeln definieren
    char Name[20];		///< Array f�r Spielername
    int Zeichen;		///< Variable zur Verarbeitung der eingelesenen Zeichen
	int key;			///< Variable zum einlesen der Zeichen von der Tastatur
	int key_old;		///< Variable zum speichern des letzen eingelesenen Zeichens
	int score;			///< Variable f�r den Score
	int comport;		///< Variable f�r die Portnummer
	int winner;			///< Variable f�r R�ckgabewert der Highscorefunktion
						///< Wird 1 wenn Highscore geknackt wurde, sonst 0
	char* argument;
	int i = 0;


	// Bildschirm l�schen
	ClearWindow();

	// Spielernamen einlesen
	SelectFont("Arial MS", 15, FONT_NORMAL);
	DrawTextXY (50, 50, COL_GREEN, "Bitte Namen eingeben:");
	while((key = GetKeyPress()) != W_KEY_RETURN ){
		Zeichen = key;
		// Anzahl der Zeichen begrenzen, Leertaste unterdr�cken
		if ((Zeichen >= ' ')&&(i < 19) && (Zeichen != 0x20) ){
			Name[i] = Zeichen;
			Name[i+1] = '\0';
			i++;
		}

		// M�glichkeit Zeichen zu l�schen
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
		 // wenn g�ltig
			comport = argument[0] - '0';
		}
	 }


	 if (InitSerialPort(comport, Bd9600, P_NONE, 8, 1) == 0)	// COM1
	 {
		 printf("\nPort opened: COM%d", comport);
		 do
	     {

			 if(IsKeyPressReady())	// Wenn Taste gedr�ckt
			 {
	        	key = GetKeyPress();

				switch(key)
				{
				case W_KEY_CURSOR_UP:
					if(key_old != W_KEY_CURSOR_DOWN)
					{
						key = 'u';
					}
					break;
				case W_KEY_CURSOR_DOWN:
					if(key_old != W_KEY_CURSOR_UP)
					{
						key = 'd';
					}
					break;
				case W_KEY_CURSOR_LEFT:
					if(key_old != W_KEY_CURSOR_RIGHT)
					{
						key = 'l';
					}
					break;
				case W_KEY_CURSOR_RIGHT:
					if(key_old != W_KEY_CURSOR_LEFT)
					{
						key = 'r';
					}
					break;
				case W_KEY_ESCAPE:
				case W_KEY_CLOSE_WINDOW:
					ShutdownSerialPort();
					return 0;
					break;
				default:
					key = NO_VALID_KEY;
					break;
				}
				// Nur wenn Key g�ltig ist und der Wert ge�ndert hat ein Zeichen ans Carmekit senden
				if((key > 0) && (key != key_old))
				{
					 putc(key,stdout);
					 SendByteToSerialPort(key);
					 // Alter Wert speichern
					 key_old = key;
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

/*****************************************************************************/
/*  Ende Modul Game                                          				 */
/*****************************************************************************/
