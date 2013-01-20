/*****************************************************************************/
/*  Modul      :   Game                                         Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   :   Kommunikation mit dem Carme-Kit �ber die serielle Schnitt-*/
/*				   stelle, Start des Spiels und Verarbeitung des Scores		 */
/*                                                                           */
/*  Bearbeiter :   M.Schl�ppi                                                */
/*                                                                           */
/*  History    :   18.03.2012 schlm19 erstellt                               */
/*				   24.12.2012 ambup1  Kopiert von Tequiz-Spiel und Total�ber-*/
/*									  arbeitung und Anpassung an Carme-Snake */
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
/*  Bearbeiter : Marcel Schl�ppi                                             */
/*                                                                           */
/*  History    : 18.03.2012 schlm19 erstellt 						         */
/*               01.04.2012 erste Versuche mit Spielfeld / Bewegung          */
/*               02.04.2012 Funktionalit�t in Funktionen ausgelagert         */
/*				 20.06.2012 �berarbeitet									 */
/*				 24.12.2012 ambup1 Kopiert von Tequiz, Total�berarbeitung und*/
/*							Anpassung an Carme-Snake						 */
/*                                                                           */
/*****************************************************************************/


/**
 * Steuerung des eigentlichen Spiels.
 * Liest den Spielername ein, verabreitet die Steuerbefehle f�r die Schlange und den Score
 *
 * Flowchart:
 * <img src="../../game_highscore_Flowchart.png">
 */

int Game(int port, const char *ApplicationPath) {

	// Variabeln definieren
    char Name[20];		// Array f�r Spielername
    int Zeichen;		// Variable zur Verarbeitung der eingelesenen Zeichen
	int key;			// Variable zum einlesen der Zeichen von der Tastatur
	int dir = 0;		// Variable zum speichern der Richtung
	int dir_old = 0;	// Variable zum speichern der letzten Richtung
	int score;			// Variable f�r den Score
	int winner;			// Variable f�r R�ckgabewert der Highscorefunktion
						// Wird 1 wenn Highscore geknackt wurde, sonst 0
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

	DrawTextXY (50, 80, COL_GREEN, "Now playing! [ESC] to escape");

	 if (InitSerialPort(port, Bd9600, P_NONE, 8, 1) == 0)	// COM1
	 {
		 printf("\nPort opened: COM%d", port);
		 do
	     {
			 if(IsKeyPressReady())	// Wenn Taste gedr�ckt
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
				// Nur wenn Key g�ltig ist und der Wert ge�ndert hat ein Zeichen ans Carmekit senden
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
	     SelectFont("Arial MS", 20, FONT_ITALIC);

	     if(winner == 1)
	     {
	    	 DrawTextXY (220, 200, COL_GREEN, "Du hast den High Score geknackt!");
	     }
	     else
	     {
	    	 DrawTextXY (220, 200, COL_GREEN, "Game over.");
	     }

	     SelectFont("Arial MS", 15, FONT_NORMAL);
	     DrawTextXY (220, 230, COL_GREEN, "Press any key to continue.");

	     while(!IsKeyPressReady())
	    	 ;
	  }

	return 0;
}

/****************************************************************************/
/*	Ende Funktion Game      												*/
/****************************************************************************/

/*****************************************************************************/
/*  Ende Modul Game                                          				 */
/*****************************************************************************/
