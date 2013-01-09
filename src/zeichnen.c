/*****************************************************************************/
/*  Modul      :   Zeichnen                                     Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   :   Zuständig für sämtliche Anzeigen während des Spiel-       */
/*                 verlaufs.                                                 */
/*                                                                           */
/*  Bearbeiter :   P. Ambuehl                                                */
/*                                                                           */
/*  History    :   24.12.2012 erstellt ambup1	                             */
/*                                                                           */
/*  File Name  :   zeichnen.c                                                */
/*                                                                           */
/*****************************************************************************/

/* Files importieren */
#include "window.h"
#include "highscore.h"
#include "zeichnen.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>





/*****************************************************************************/
/*  Funktion   : Menu zeichnen	               	                Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   : Erzeugt die Anzeigen des Hauptmenus.					     */
/*                                                                           */
/*  Bearbeiter : Peter Ambühl	                                             */
/*                                                                           */
/*  History    : 24.12.2012 erstellt ambup1							         */
/*                                                                           */
/*****************************************************************************/

void Menu_zeichnen(void){
	/* Hauptmenu Anzeigen zeichnen */
	SelectFont("Arial MS", 45, FONT_BOLD);
	DrawTextXY (250, 70, COL_GREEN, "CARME-SNAKE");
	SelectFont("Arial MS", 30, FONT_NORMAL);
	DrawTextXY (240, 230, COL_GREEN, "1 Spiel starten");
	DrawTextXY (236, 300, COL_YELLOW, "2 Hall of Fame");
	DrawTextXY (230, 370, COL_RED, "3 Spiel beenden");
	DrawTextXY (80, 530, COL_GREEN, "P. Ambühl, M. Bärtschi, C. Stoller");
}


/*****************************************************************************/
/*  Funktion   : Highscore zeichnen                             Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   : Zeichnet die Highscoreliste.							     */
/*                                                                           */
/*  Bearbeiter : Peter Ambuehl	                                             */
/*                                                                           */
/*  History    : 24.12.2012 erstellt ambup1							         */
/*                                                                           */
/*****************************************************************************/

/**
 * Bildet die Highscoreliste auf dem Bildschirm ab.
 */

void Highscore_zeichnen(const char *ApplicationPath){

	char Name[1];
	Name[0]='a';
	int index;
	char ausgabe2[100];

	highscore(Name, 1, ApplicationPath);
	ClearWindow ();

	SelectFont("Arial MS", 30, FONT_BOLD);
	DrawTextXY (220, 50, COL_GREEN, "Highscoreliste");

	// Zeichnet die Highscoreliste
	SelectFont("Arial MS", 30, FONT_NORMAL);
	for(index=9; index>=0; index--){

		// Umwandlung der Punke

		sprintf(ausgabe2,"%d",topten[index].score);

		// Name und zugehörige Punkte darstellen

		DrawTextXY (50, 150+index*40, COL_GREEN, topten[index].name);
		DrawTextXY (530, 150+index*40, COL_RED, ausgabe2);
	}
}

/****************************************************************************/
/*	Ende Funktion Highscore zeichnen    									*/
/****************************************************************************/

/*****************************************************************************/
/*  Ende Modul Zeichnen                                       				 */
/*****************************************************************************/
