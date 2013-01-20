/*****************************************************************************/
/*  Modul      : Hauptmodul                                     Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   : Enth�lt Menufunktionalit�t und ruft externe                 */
/* 				 Module auf.												 */
/*                                                                           */
/*  Bearbeiter : Marcel Schl�ppi                                             */
/*                                                                           */
/*  History    : 09.03.2012 Basis_Projekt importiert schlm19                 */
/*				 24.12.2012 Kopiert von Tequiz-Spiel, �berarbeitet und		 */
/*							angepasst an Carme-Snake						 */
/*                                                                           */
/*  File Name  : Snake_main.c                                                */
/*                                                                           */
/*****************************************************************************/

/**
 * \file Snake_main.c
 * Hauptmodul, enth�lt Menufunktionalit�t und ruft externe Module auf.
 */

/* Files importieren */
#include "window.h"
#include "zeichnen.h"
#include "game.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*****************************************************************************/
/*  Funktion   : Hauptprogramm                                  Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   : Enth�lt Menufunktionalit�t und ruft externe                 */
/* 				 Module auf.												 */
/*                                                                           */
/*  History    : 18.03.2012 Nicht ben�tigten Demo-Code gel�scht schlm19      */
/*               19.06.2012 �berarbeiter schlm19                             */
/*               23.06.2012 Hauptmenu hinzugef�gt schlm19                    */
/*				 24.12.2012 ambup1 Kopiert von Tequiz-Spiel, �berarbeitet und*/
/*							angepasst an Carme-Snake						 */
/*                                                                           */
/*****************************************************************************/

/**
 * Mainfunktion des Spiels PC-seitig.
 * Zeigt ein Menu auf dem PC-Bildschirm an,
 * welches die Optionen Spiel starten,
 * Highscore anzeigen, und Spiel beenden an.
 * Ruft externe Grafikfunktionen und game(...)
 * @return gibt 0 zur�ck
 */
int gfxmain(int argc, char* argv[], const char *ApplicationPath)
{

	/* Grafikfenster initialisieren und �ffnen */
	InitGraphic(-1, -1);

	/* Bildschirm l�schen */
	ClearWindow();

	int Key=0;
	Menu_zeichnen();

	/* Taste einlesen */
	while(1){
		while (IsKeyPressReady()){
			Key = GetKeyPress();
		}
		if(Key=='1'){

			/* Game aufrufen */
			Game(argc, argv, ApplicationPath);

			/* Hauptmenu anzeigen */
			Key=0;
			ClearWindow();
			Menu_zeichnen();
		}
		if(Key=='2'){

			/* Highscorelise anzeigen */
			Highscore_zeichnen(ApplicationPath);
			WaitMs(5000);
			InitGraphic(-1, -1);

			/* Hauptmenu anzeigen */
			Key=0;
			ClearWindow();
			Menu_zeichnen();
		}
		if(Key=='3'){

			/* Grafikfenster schliessen */
			CloseGraphic();

			/* Programmende - Fehlerlose Ausf�hrung zur�ckmelden */
			return 0;
		}
	}
}
/****************************************************************************/
/*	Ende Hauptprogramm														*/
/****************************************************************************/
/*****************************************************************************/
/*  Ende Modul Hauptprogramm                                   				 */
/*****************************************************************************/
