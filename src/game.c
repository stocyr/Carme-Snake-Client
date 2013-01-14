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
	int dir = 0;		///< Variable zum speichern der Richtung
	int dir_old = 0;	///< Variable zum speichern der letzten Richtung
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
			 if(IsKeyPressReady())	// Wenn Taste gedrückt
			 {
	        	key = GetKeyPress();

				switch(key)
				{
				case W_KEY_CURSOR_UP:
					if(dir_old != 'd')
					{
						dir = 'u';
					}
					break;
				case W_KEY_CURSOR_DOWN:
					if(dir_old != 'u')
					{
						dir = 'd';
					}
					break;
				case W_KEY_CURSOR_LEFT:
					if(dir_old != 'r')
					{
						dir = 'l';
					}
					break;
				case W_KEY_CURSOR_RIGHT:
					if(dir_old != 'l')
					{
						dir = 'r';
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
				// Nur wenn Key gültig ist und der Wert geändert hat ein Zeichen ans Carmekit senden
				if(dir != dir_old)
				{
					 SendByteToSerialPort(dir);
					 // Alter Wert speichern
					 dir_old = dir;
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
