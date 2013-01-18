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
	SelectFont("Bauhaus 93", 45, FONT_BOLD);
	DrawTextXY (800, 300, COL_BLUE, "CARME-SNAKE");
	SelectFont("Papyrus", 30, FONT_NORMAL);
	DrawTextXY (240, 230, COL_GREEN, "1 Spiel starten");
	DrawTextXY (240, 300, COL_LIGHTBLUE, "2 Hall of Fame");
	DrawTextXY (240, 370, COL_YELLOW, "3 Comport wählen");
	DrawTextXY (240, 440, COL_RED, "4 Spiel beenden");
	SelectFont("Agency FB", 16, FONT_NORMAL);
	DrawTextXY (600, 530, COL_LIGHTBLUE, "P. Ambühl, M. Bärtschi, C. Stoller");
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

	SelectFont("Bauhaus 93", 30, FONT_BOLD);
	DrawTextXY (220, 50, COL_BLUE, "Highscoreliste");

	// Zeichnet die Highscoreliste
	SelectFont("Papyrus", 30, FONT_NORMAL);
	for(index=9; index>=0; index--){

		// Umwandlung der Punke

		sprintf(ausgabe2,"%d",topten[index].score);

		// Name und zugehörige Punkte darstellen

		DrawTextXY (50, 150+index*40, COL_LIGHTBLUE, topten[index].name);
		DrawTextXY (530, 150+index*40, COL_RED, ausgabe2);
	}
}

/****************************************************************************/
/*	Ende Funktion Highscore zeichnen    									*/
/****************************************************************************/

/*****************************************************************************/
/*  Ende Modul Zeichnen                                       				 */
/*****************************************************************************/
